#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Game;
class Player;
class RockOn;

/// <summary>
/// ゴール【ロックオン】
/// </summary>
class Goal : public RockOnObject
{
public:

	Goal();
	~Goal();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	float GetLength()
	{
		return m_length.Length();
	}

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
	Vector3 GetPosition() const
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

private:

	/// <summary>
	/// ゴールまでの距離を判定。
	/// </summary>
	void Length();

	/// <summary>
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	FontRender						m_fontRender;
	ModelRender						m_modelRender;
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Vector3							m_length;
	Quaternion						m_rotation;

	Game*							m_game;
	Player*							m_player;
	RockOn*							m_rockOn;

	int								m_state = 0;
	bool							m_isHit = false;

	EffectEmitter*					m_goalEffect;
};