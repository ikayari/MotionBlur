#include "stdafx.h"
#include "SpeedUpRail.h"

#include "Player.h"
#include "RockOn.h"

SpeedUpRail::SpeedUpRail()
{

}

SpeedUpRail::~SpeedUpRail()
{

}

bool SpeedUpRail::Start()
{
	m_shoot = { 1.0f,0.0f,0.0f };
	m_rotation.Apply(m_shoot);

	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);
	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/SpeedUpRail.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/SpeedUp.wav");

	m_ghostCollider.CreateBox(m_position, m_rotation, { 1000.0f,500.0f,1000.0f });

	return true;
}

void SpeedUpRail::Update()
{
	m_modelRender.Update();
	Hit();

	wchar_t x[256];
	swprintf_s(x, 256, L"SpeedUp");
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f,100.0f, 0.0f });
}

void SpeedUpRail::Render(RenderContext& rc)
{
	if (m_coolTime <= 1.0f)
	{
#ifdef K2_DEBUG
		m_fontRender.Draw(rc);
#endif
	}

	m_modelRender.Draw(rc);
}

void SpeedUpRail::Hit()
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
		m_speedUpSE = NewGO<SoundSource>(6);
		m_speedUpSE->Init(6);
		m_speedUpSE->SetVolume(0.3f);
		m_speedUpSE->Play(false);
		m_coolTime = 0.0f;
		Vector3 zero = Vector3::Zero;				//スピードを0にする。
		m_player->SetMoveSpeed(zero);				//スピードを0にする。
		Vector3 shoot = m_shoot;
		shoot *= 350000000.0f;
		m_player->SetMoveSpeed(shoot);
		m_isHit = false;

		g_pad[0]->SetVibration(0.5f, 0.5f);
	}
}