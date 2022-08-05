#pragma once

/// <summary>
/// ステージ上部に設置されているエンジン【非ロックオン】
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