#include "stdafx.h"
#include "Goal.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"

Goal::Goal()
{

}

Goal::~Goal()
{

}

bool Goal::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_length = m_player->GetPosition() - m_position;

	m_rockOn->AddRockOnObject(this);

	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/GoalPoint.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
	
	m_ghostCollider.CreateBox(m_position, m_rotation, { 10000.0f,10000.0f,100.0f });
	EffectEngine::GetInstance()->ResistEffect(100, u"Assets/Effect/Selfmade/ring.efk");
	m_goalEffect = NewGO<EffectEmitter>(0);
	m_goalEffect->Init(100);
	m_goalEffect->SetPosition(m_position);
	m_goalEffect->SetRotation(m_rotation);
	m_goalEffect->SetScale(Vector3::One *28);
	m_goalEffect->Play();
	return true;
}

void Goal::Update()
{
	m_modelRender.Update();
	m_length = m_player->GetPosition() - m_position;
	Hit();
	if (!m_goalEffect->IsPlay())
	{
		m_goalEffect = NewGO<EffectEmitter>(0);
		m_goalEffect->Init(100);
		m_goalEffect->SetPosition(m_position);
		m_goalEffect->SetRotation(m_rotation);
		m_goalEffect->SetScale(Vector3::One * 28);
		m_goalEffect->Play();
	}
	
}

void Goal::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Goal::Hit()
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
		m_game->SetGameState(2);
	}
}