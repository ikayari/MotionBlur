#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Game;
class Player;
class RockOn;

/// <summary>
/// �S�[���y���b�N�I���z
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

private:

	/// <summary>
	/// �S�[���܂ł̋����𔻒�B
	/// </summary>
	void Length();

	/// <summary>
	/// �����蔻��̊Ǘ��B
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