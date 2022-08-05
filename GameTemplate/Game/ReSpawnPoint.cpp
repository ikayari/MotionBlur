#include "stdafx.h"
#include "ReSpawnPoint.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"
#include "TimeLimit.h"

namespace
{
	const float EFFECT_SIZE = 230.0f;
}

ReSpawnPoint::ReSpawnPoint()
{

}

ReSpawnPoint::~ReSpawnPoint()
{

}

bool ReSpawnPoint::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");
	m_timeLimit = FindGO<TimeLimit>("timeLimit");

	m_rockOn->AddRockOnObject(this);

	m_modelRender.Init("Assets/modelData/Stage_0/RespawnPoint.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	EffectEngine::GetInstance()->ResistEffect(16, u"Assets/Effect/Selfmade/CheckPoint.efk");
	m_reSpawnPointEF = NewGO<EffectEmitter>(16);
	m_reSpawnPointEF->Init(16);
	m_reSpawnPointEF->SetPosition({ m_position.x, m_position.y + 150.0f, m_position.z });
	m_reSpawnPointEF->SetScale(Vector3::One * EFFECT_SIZE);
	EffectEngine::GetInstance()->ResistEffect(17, u"Assets/Effect/Selfmade/CheckPointDelete.efk");

	m_spriteRender.Init("Assets/sprite/CheckPoint/CheckPoint.dds", 400.0f, 400.0f);
	m_spriteRender.SetPosition({ 0.0f,250.0f,0.0f });
	m_spriteRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 220.0f,220.0f,220.0f });

	return true;
}

void ReSpawnPoint::Update()
{
	Sprite();
	Hit();
}

void ReSpawnPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	if (m_isSpriteRenderStart == true)
	{
		m_spriteRender.Draw(rc);
	}
}

void ReSpawnPoint::Sprite()
{
	//�v���C���[���`�F�b�N�|�C���g��ʉ߂�����
	if (m_isSpriteRenderStart == true && m_isSpriteRenderEnd == false)
	{
		//�摜�����X�ɕ`�悷��
		if (m_spriteScale <= 0.05f)
		{
			m_spriteScale += 0.01f;
		}
		else if (m_spriteScale >= 0.05f && m_spriteScale < 1.0f)
		{
			m_spriteScale += 0.1f;
		}
		//�摜�����S�ɕ`�悳�ꂽ��
		else if (m_spriteScale >= 1.0f)
		{
			//�摜�̏I���������J�n����
			m_isSpriteRenderEnd = true;
		}
	}

	if (m_isSpriteRenderEnd == true)
	{
		//���Ԃ��v��
		m_spriteAliveTime += g_gameTime->GetFrameDeltaTime();
	}

	//2�b�ȏ�o�߂�����
	if (m_spriteAliveTime > 2.0f)
	{
		//���X�ɉ摜�����
		m_spriteScale -= 0.1f;

		if (m_spriteScale <= 0.0f)
		{
			m_isSpriteRenderStart = false;
		}
	}

	m_spriteRender.SetScale({ 1.0f,m_spriteScale,1.0f });
	m_spriteRender.Update();
}

void ReSpawnPoint::Hit()
{
	//�L�����N�^�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g�̂����蔻����s���B
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_player->GetPlayerSpeed() >= 500.0f) {
			//m_physicsGhostObject�ƂԂ������B
			//�t���O��true�ɂ���B
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_aliveTime += g_gameTime->GetFrameDeltaTime();
		m_isSpriteRenderStart = true;
	}
	if (m_aliveTime >= 0.05f && m_isHit == true)
	{
		//�G�t�F�N�g���~�߂�B
		m_reSpawnPointEF->Stop();

		//�f���[�g���̃G�t�F�N�g���Đ�����B
		m_reSpawnPointDeleteEF = NewGO<EffectEmitter>(17);
		m_reSpawnPointDeleteEF->Init(17);
		m_reSpawnPointDeleteEF->SetScale(Vector3::One * EFFECT_SIZE);
		m_reSpawnPointDeleteEF->Play();

		//�c�莞�Ԃ�10�b���Z
		m_timeLimit->AddTime(10.0f);

		m_player->SetReSpawnPosition(m_position);
		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}