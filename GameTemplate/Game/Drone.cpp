#include "stdafx.h"
#include "Drone.h"

#include "Player.h"
#include "RockOn.h"

Drone::Drone()
{

}

Drone::~Drone()
{

}

bool Drone::Start()
{
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);

	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/Effect/Selfmade/BrokenExplosion.efk");
	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Drone.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Explosion.wav");

	m_boxCollider.BoxInit({ 500.0f,500.0f,500.0f }, m_position, 0.1);
	m_ghostCollider.CreateBox(m_position, m_rotation, { 540.0f,540.0f,540.0f });

	return true;
}

void Drone::Update()
{
	m_modelRender.Update();
	Hit();
}

void Drone::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Drone::Hit()
{
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_aliveTime += g_gameTime->GetFrameDeltaTime();
	}
	if (m_aliveTime >= 0.05f && m_isHit == true)
	{
		m_explosion = NewGO<EffectEmitter>(4);
		m_explosion->Init(4);
		m_explosion->SetScale(Vector3::One * 200.0f);
		m_explosion->SetPosition({ m_position.x,m_position.y += 10.0f,m_position.z });
		m_explosion->Play();

		m_explosionSE = NewGO<SoundSource>(5);
		m_explosionSE->Init(5);
		m_explosionSE->SetVolume(0.3f);
		m_explosionSE->Play(false);

		m_state = 1;
		m_boxCollider.RemoveRigidBoby();
		m_ghostCollider.Release();
		m_isHit = false;

		g_pad[0]->SetVibration(0.5f, 0.5f);
	}
}