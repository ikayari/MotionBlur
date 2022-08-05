#include "stdafx.h"
#include "Door.h"

#include "Player.h"
#include "RockOn.h"

Door::Door()
{

}

Door::~Door()
{

}

bool Door::Start()
{
	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO<Player>("player");

	m_open[enAnimationClip_Open].Load("Assets/animData/Door.tka");
	m_open[enAnimationClip_Idle].Load("Assets/animData/Door_Idle.tka");
	m_open[enAnimationClip_Open].SetLoopFlag(false);
	m_open[enAnimationClip_Idle].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/Stage_0/Door.tkm", m_open,enAnimationClip_Num);

	m_modelRender.SetPosition(m_position.x, m_position.y - 800.0f, m_position.z);
	m_modelRender.SetScale(m_scale * 1.3f);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
	m_ghostCollider.CreateBox(m_position, m_rotation, { 2000.0f,2000.0f,3000.0f });

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/Door.wav");
	
	return true;
}

void Door::Update()
{
	m_modelRender.Update();
	Hit();

	wchar_t x[256];
	swprintf_s(x, 256, L"Open");
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f, 50.0f, 0.0f });
}

void Door::Render(RenderContext& rc)
{
	if (m_coolTime <= 1.0f)
	{
#ifdef K2_DEBUG
		m_fontRender.Draw(rc);
#endif
	}

	m_modelRender.Draw(rc);
}

void Door::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	if (m_state == 1)
	{
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.0f);
	}

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
		m_openSE = NewGO<SoundSource>(4);
		m_openSE->Init(4);
		m_openSE->SetVolume(0.2f);
		m_openSE->Play(false);
		m_modelRender.PlayAnimation(enAnimationClip_Open, 0.0f);
		m_ghostCollider.Release();
		m_coolTime = false;
		m_isHit = false;
	}
}