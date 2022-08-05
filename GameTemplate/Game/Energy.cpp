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
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;

			//エフェクトストップ
			m_energy->Stop();
			m_energy->Dead();
			m_energy->Deactivate();
		}
		});

	if (m_isHit == true)
	{
		//爆発エフェクト
		m_explosion = NewGO<EffectEmitter>(4);
		m_explosion->Init(4);
		m_explosion->SetScale(Vector3::One * 30.0f);
		m_explosion->SetPosition(m_position);
		m_explosion->Play();

		//残り時間に2秒加算
		m_timeLimit->AddTime(2.0f);

		//バイブレーション
		g_pad[0]->SetVibration(0.5f, 0.1f);

		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}