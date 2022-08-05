#include "stdafx.h"
#include "Energy.h"

#include "Player.h"
#include "RockOn.h"
#include "TimeLimit.h"

Energy::Energy()
{

}

Energy::~Energy()
{

}

bool Energy::Start()
{
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");
	m_timeLimit = FindGO<TimeLimit>("timeLimit");

	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/Effect/Selfmade/BrokenExplosion.efk");
	EffectEngine::GetInstance()->ResistEffect(20, u"Assets/Effect/Selfmade/Energy.efk");

	m_energy = NewGO<EffectEmitter>(20);
	m_energy->Init(20);
	m_energy->SetScale(Vector3::One * 70.0f);
	m_energy->SetPosition({ m_position.x,m_position.y,m_position.z });
	m_energy->Play();

	m_modelRender.Init("Assets/modelData/Stage_0/Energy.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 205.0f,205.0f,205.0f });

	return true;
}

void Energy::Update()
{
	m_modelRender.Update();
	Hit();
}

void Energy::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Energy::Hit()
{
	//�L�����N�^�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g�̂����蔻����s���B
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObject�ƂԂ������B
			//�t���O��true�ɂ���B
			m_isHit = true;

			//�G�t�F�N�g�X�g�b�v
			m_energy->Stop();
			m_energy->Dead();
			m_energy->Deactivate();
		}
		});

	if (m_isHit == true)
	{
		//�����G�t�F�N�g
		m_explosion = NewGO<EffectEmitter>(4);
		m_explosion->Init(4);
		m_explosion->SetScale(Vector3::One * 30.0f);
		m_explosion->SetPosition(m_position);
		m_explosion->Play();

		//�c�莞�Ԃ�2�b���Z
		m_timeLimit->AddTime(2.0f);

		//�o�C�u���[�V����
		g_pad[0]->SetVibration(0.5f, 0.1f);

		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}