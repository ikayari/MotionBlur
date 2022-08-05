#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

/// <summary>
/// ジャンプ台【非ロックオン】
/// </summary>
class JumpBoard : public IGameObject
{
public:

	JumpBoard();
	~JumpBoard();
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
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	FontRender						m_fontRender;

	ModelRender						m_modelRender;
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Vector3							m_shoot;
	Quaternion						m_rotation;

	SoundSource*					m_jumpSE;
	Player*							m_player;
	RockOn*							m_rockOn;

	bool							m_isHit = false;
	float							m_coolTime = 1.0f;
};