#pragma once

/// <summary>
/// �X�e�[�W�㕔�ɐݒu����Ă���G���W���y�񃍃b�N�I���z
/// </summary>
class Engine : public IGameObject
{
public:

	Engine();
	~Engine();
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

private:

	enum EnAnimationClip {
		enAnimationClip_Rot,
		enAnimationClip_Num
	};

	ModelRender						m_modelRender;
	AnimationClip					m_animation[enAnimationClip_Num];
	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;
};