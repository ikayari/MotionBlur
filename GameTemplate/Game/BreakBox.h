#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;
class TimeLimit;

/// <summary>
/// �j��\�ȃ{�b�N�X�y���b�N�I���z
/// </summary>
class BreakBox : public RockOnObject
{
public:

	BreakBox();
	~BreakBox();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���Z�b�g�X�e�[�g��ݒ�Btrue�Ń��Z�b�g�B
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	bool SetReSetState(const bool& state)
	{
		m_reSetState = state;
		return 0;
	}

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

	/// <summary>
	///	�����������B
	/// </summary>
	void ReSet();

	EffectEmitter*					m_explosion;
	ModelRender						m_modelRender;
	CharacterController				m_boxCollider;
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;

	SoundSource*					m_explosionSE;
	Player*							m_player;
	RockOn*							m_rockOn;
	TimeLimit*						m_timeLimit;

	int								m_state = 0;
	bool							m_reSetState = false;
	bool							m_isHit = false;
	float							m_aliveTime = 0.0f;
};