#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Game;
class Player;
class RockOn;
class TimeLimit;

/// <summary>
/// ���X�|�[���n�_�y���b�N�I���z
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
	/// �摜�̊Ǘ�
	/// </summary>
	void Sprite();

	/// <summary>
	/// �����蔻��̊Ǘ��B
	/// </summary>
	void Hit();

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
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
	float							m_currentAlpha = 0.0f;		//a�l�B
};