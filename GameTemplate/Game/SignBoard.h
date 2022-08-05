#pragma once

/// <summary>
/// 進行方向を示す掲示板【非ロックオン】
/// </summary>
class SignBoard : public IGameObject
{
public:

	SignBoard();
	~SignBoard();
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

private:

	ModelRender						m_modelRender;
	PhysicsStaticObject				m_phyStaticObject;
	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;
};