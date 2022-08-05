#pragma once

/// <summary>
/// �X�e�[�W1
/// </summary>
class Stage_1_Stage : public IGameObject
{
public:

	Stage_1_Stage();
	~Stage_1_Stage();
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

	ModelRender						m_modelRender;
	PhysicsStaticObject				m_phyStaticObject;
	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;
};