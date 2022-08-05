#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;
class TimeLimit;

/// <summary>
/// エネルギー【ロックオン】
/// </summary>
class Energy : public IGameObject
{
public:

	Energy();
	~Energy();
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
	/// <summary>
	///	ステートを取得。
	/// </summary>
	/// <returns></returns>
	int GetState() const
	{
		return m_state;
	}

private:

	/// <summary>
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	EffectEmitter*					m_explosion;
	EffectEmitter*					m_energy;
	ModelRender						m_modelRender;
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;

	Player*							m_player;
	RockOn*							m_rockOn;
	TimeLimit*						m_timeLimit;

	int								m_state = 0;
	bool							m_isHit = false;
	float							m_aliveTime = 0.0f;
};