#include "stdafx.h"
#include "JumpBoard.h"

#include "Player.h"
#include "RockOn.h"

JumpBoard::JumpBoard()
{

}

JumpBoard::~JumpBoard()
{

}

bool JumpBoard::Start()
{
	m_shoot = { 0.0f,0.0f,-1.0f };
	m_rotation.Apply(m_shoot);

	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO<Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/JumpBoard.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/Jump.wav");
	
	m_ghostCollider.CreateBox(m_position, m_rotation, { 2000.0f,2000.0f,600.0f });

	return true;
}

void JumpBoard::Update()
{
	m_modelRender.Update();
	Hit();

	wchar_t x[256];
	swprintf_s(x, 256, L"Jump");
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f, 150.0f, 0.0f });
}

void JumpBoard::Render(RenderContext& rc)
{

	if (m_coolTime <= 1.0f)
	{
#ifdef K2_DEBUG
		m_fontRender.Draw(rc);
#endif
	}

	m_modelRender.Draw(rc);
}

void JumpBoard::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_coolTime >= 1.0f) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		//サウンドを再生
		m_jumpSE = NewGO<SoundSource>(7);
		m_jumpSE->Init(7);
		m_jumpSE->SetVolume(0.1f);
		m_jumpSE->Play(false);
		m_coolTime = 0.0f;
		Vector3 zero = Vector3::Zero;				//スピードを0にする。
		m_player->SetMoveSpeed(zero);				//スピードを0にする。
		Vector3 shoot = m_shoot;
		shoot *= 50000000.0f;
		m_player->SetMoveSpeed(shoot);
		m_isHit = false;

		g_pad[0]->SetVibration(3.0f, 0.5f);
	}
}