#include "stdafx.h"
#include "Turret.h"

#include "Player.h"
#include "RockOn.h"

namespace
{
	float CHARGE_TIME = 2.0f;
	float COOL_TIME = 3.1f;
	float ALIVE_TIME = 1.0f;
}

Turret::Turret()
{

}

Turret::~Turret()
{

}

bool Turret::Start()
{
	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO <Player>("player");

	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Turret.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	EffectEngine::GetInstance()->ResistEffect(5, u"Assets/Effect/Selfmade/Beam.efk");
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/Effect/Selfmade/BeamCharge.efk");

	m_boxCollider.BoxInit({ 300.0f,500.0f,300.0f }, m_position, 0.05);

	m_effectRotation = m_rotation;
	m_effectRotation.AddRotationDegY(180.0f);

	return true;
}

void Turret::Update()
{
	m_modelRender.Update();
	Hit();
}

void Turret::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Turret::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	if (m_coolTime >= CHARGE_TIME)
	{
		if (m_chargeEffectCoolTime == false)
		{
			m_beamCharge = NewGO<EffectEmitter>(9);
			m_beamCharge->Init(9);
			m_beamCharge->SetScale(Vector3::One * 50.0f);
			m_beamCharge->SetPosition({ m_position.x, m_position.y + 100.0f, m_position.z });
			m_beamCharge->SetRotation(m_effectRotation);
			m_beamCharge->Play();
			m_chargeEffectCoolTime = true;
		}

		if (m_coolTime >= COOL_TIME)													//クールタイムが終わったら
		{
			if (m_beamEffectCoolTime == false)												//エフェクトを再生
			{
				m_beam = NewGO<EffectEmitter>(5);
				m_beam->Init(5);
				m_beam->SetRotation(m_effectRotation);
				m_beam->SetScale(Vector3::One * 150.0f);
				m_beam->SetPosition({ m_position.x,m_position.y + 130.0f,m_position.z });
				m_beam->Play();
				m_beamEffectCoolTime = true;
			}
			m_beamCollider.CreateBox(m_position, m_rotation, { 3000.0f,300.0f,50.0f });	//当たり判定を生成
			m_state = 1;
			m_aliveTime += g_gameTime->GetFrameDeltaTime();
		}
	}

	if (m_aliveTime >= ALIVE_TIME)
	{
		m_beamCollider.Release();
		m_chargeEffectCoolTime = false;
		m_beamEffectCoolTime = false;
		m_state = 0;
		m_coolTime = 0.0f;
		m_aliveTime = 0.0f;
	}
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_beamCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)					//ビームがプレイヤーに当たったら
	{
		m_player->SetState(1);
		//バイブレーション
		g_pad[0]->SetVibration(0.4f, 0.1f);
		m_isHit = false;
	}
}