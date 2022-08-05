#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

/// <summary>
/// �h�A�y�񃍃b�N�I���z
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
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
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
	/// �X�e�[�g��ݒ�
	/// </summary>
	/// <param name="num"></param>
	void SetState(const int& num)
	{
		m_state = num;
	}

private:

	/// <summary>
	/// �����蔻��̊Ǘ��B
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