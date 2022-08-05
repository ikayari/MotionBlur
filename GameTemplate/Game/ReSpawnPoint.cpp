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
	//プレイヤーがチェックポイントを通過したら
	if (m_isSpriteRenderStart == true && m_isSpriteRenderEnd == false)
	{
		//画像を徐々に描画する
		if (m_spriteScale <= 0.05f)
		{
			m_spriteScale += 0.01f;
		}
		else if (m_spriteScale >= 0.05f && m_spriteScale < 1.0f)
		{
			m_spriteScale += 0.1f;
		}
		//画像が完全に描画されたら
		else if (m_spriteScale >= 1.0f)
		{
			//画像の終了処理を開始する
			m_isSpriteRenderEnd = true;
		}
	}

	if (m_isSpriteRenderEnd == true)
	{
		//時間を計る
		m_spriteAliveTime += g_gameTime->GetFrameDeltaTime();
	}

	//2秒以上経過したら
	if (m_spriteAliveTime > 2.0f)
	{
		//徐々に画像を閉じる
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
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_player->GetPlayerSpeed() >= 500.0f) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
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
		//エフェクトを止める。
		m_reSpawnPointEF->Stop();

		//デリート時のエフェクトを再生する。
		m_reSpawnPointDeleteEF = NewGO<EffectEmitter>(17);
		m_reSpawnPointDeleteEF->Init(17);
		m_reSpawnPointDeleteEF->SetScale(Vector3::One * EFFECT_SIZE);
		m_reSpawnPointDeleteEF->Play();

		//残り時間に10秒加算
		m_timeLimit->AddTime(10.0f);

		m_player->SetReSpawnPosition(m_position);
		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}