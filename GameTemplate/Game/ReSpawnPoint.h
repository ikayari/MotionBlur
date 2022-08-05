#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Game;
class Player;
class RockOn;
class TimeLimit;

/// <summary>
/// リスポーン地点【ロックオン】
/// </summary>
class ReSpawnPoint : public RockOnObject
{
public:

	ReSpawnPoint();
	~ReSpawnPoint();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const override
	{
		return m_position;
	}
	/// <summary>
	/// サイズを設定。
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	///	ステートを取得。
	/// </summary>
	/// <returns></returns>
	int GetState() const override
	{
		return m_state;
	}

private:

	/// <summary>
	/// 画像の管理
	/// </summary>
	void Sprite();

	/// <summary>
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	enum EnState {
		enState_FadeIn,			//フェードイン中。
		enState_FadeOut,		//フェードアウト中。
		enState_Idle,			//アイドル中。
	};
	EnState							m_fadeState;

	EffectEmitter*					m_reSpawnPointEF;
	EffectEmitter*					m_reSpawnPointDeleteEF;

	SpriteRender					m_spriteRender;
	ModelRender						m_modelRender;
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;

	Game*							m_game;
	Player*							m_player;
	RockOn*							m_rockOn;
	TimeLimit*						m_timeLimit;

	int								m_state = 0;
	bool							m_isStart = true;
	bool							m_isSpriteRenderStart = false;
	bool							m_isSpriteRenderEnd = false;
	bool							m_isHit = false;
	float							m_spriteScale = 0.0f;
	float							m_aliveTime = 0.0f;
	float							m_spriteAliveTime = 0.0f;
	float							m_currentAlpha = 0.0f;		//a値。
};