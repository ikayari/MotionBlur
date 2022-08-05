#pragma once

/// <summary>
/// �i�b�g�y�񃍃b�N�I���z
/// </summary>
class Nut : public IGameObject
{
public:

	Nut();
	~Nut();
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