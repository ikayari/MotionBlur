#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;
class TimeLimit;

/// <summary>
/// �G�l���M�[�y���b�N�I���z
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
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �T�C�Y��ݒ�B
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	///	�X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	int GetState() const
	{
		return m_state;
	}

private:

	/// <summary>
	/// �����蔻��̊Ǘ��B
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