#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

/// <summary>
/// �^���b�g�y�񃍃b�N�I���z
/// </summary>
class Turret : public RockOnObject
{
public:

	Turret();
	~Turret();
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
	Vector3 GetPosition() const override
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
	int GetState() const override
	{
		return m_state;
	}


private:

	/// <summary>
	/// �����蔻��̊Ǘ��B
	/// </summary>
	void Hit();

	EffectEmitter*					m_beam;
	EffectEmitter*					m_beamCharge;

	ModelRender						m_modelRender;
	CharacterController				m_boxCollider;
	PhysicsGhostObject				m_beamCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;
	Quaternion						m_effectRotation;

	Player*							m_player;
	RockOn*							m_rockOn;

	int								m_state = 0;
	bool							m_isHit = false;
	bool							m_beamEffectCoolTime = false;
	bool							m_chargeEffectCoolTime = false;
	float							m_coolTime = 0.0f;
	float							m_aliveTime = 0.0f;
};