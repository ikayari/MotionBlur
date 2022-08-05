#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

/// <summary>
/// ドア【非ロックオン】
/// </summary>
class Door : public IGameObject
{
public:

	Door();
	~Door();
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
	/// <summary>
	/// ステートを設定
	/// </summary>
	/// <param name="num"></param>
	void SetState(const int& num)
	{
		m_state = num;
	}

private:

	/// <summary>
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Open,
		enAnimationClip_Num
	};

	FontRender						m_fontRender;

	ModelRender						m_modelRender;
	AnimationClip					m_open[enAnimationClip_Num];
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;

	SoundSource*					m_openSE;

	Player*							m_player;
	RockOn*							m_rockOn;

	int								m_state = 0;
	bool							m_isHit = false;
	float							m_coolTime = 0.0f;

};