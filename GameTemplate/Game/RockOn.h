#pragma once

#include <RockOnObject.h>

class Bumper;
class Player;

/// <summary>
/// ���b�N�I��
/// </summary>
class RockOn : public IGameObject
{
public:
	RockOn();
	~RockOn();
	bool Start();
	void Render(RenderContext& rc);
	void Update();

	/// <summary>
	/// ���b�N�I�����Ă邩�ۂ��̔�����擾
	/// </summary>
	/// <returns></returns>
	bool GetRockOnJudge() const
	{
		return m_isRockOn;
	}

	/// <summary>
	/// ���b�N�I���I�u�W�F�N�g�ƃv���C���[�̒����������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetDifference() const
	{
		return m_difference;
	}

	/// <summary>
	/// ���b�N�I���o����I�u�W�F�N�g�Ƃ��ēo�^
	/// </summary>
	/// <param name="addObject"></param>
	void AddRockOnObject(RockOnObject* addObject)
	{
		m_rockOnObject.push_back(addObject);
	}

private:

	/// <summary>
	/// ���b�N�I�����邩�ۂ��̔��������B
	/// </summary>
	void Judge();

	/// <summary>
	/// �摜�̕`�揈�����Ǘ��B
	/// </summary>
	void Sprite();

	//�摜
	SpriteRender m_rockOn_1;
	SpriteRender m_rockOn_2;
	SpriteRender m_rockOn_3;
	SpriteRender m_rockOn_4;
	SpriteRender m_rockOn_5;
	SpriteRender m_rockOn_6;
	SpriteRender m_rockOn_7;
	SpriteRender m_rockOn_8;

	float m_rotation_Num1;
	float m_rotation_Num2;
	float m_rotation_Num3;
	float m_rotation_Num4;
	float m_rotation_Num5;
	float m_rotation_Num6;
	float m_rotation_Num7;
	float m_rotation_Num8;

	Quaternion m_rotation_1;
	Quaternion m_rotation_2;
	Quaternion m_rotation_3;
	Quaternion m_rotation_4;
	Quaternion m_rotation_5;
	Quaternion m_rotation_6;
	Quaternion m_rotation_7;
	Quaternion m_rotation_8;

	Vector2 m_2DPosition;
	Vector3 m_position;
	Vector3 m_difference;
	Vector3 m_RockOnPosition;

	std::vector<Bumper*> m_bumpers;
	std::vector<RockOnObject*> m_rockOnObject;
	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;

	int m_bumperSize;

	float m_rockOnSize_1 = 1.0f;
	float m_rockOnSize_2 = 1.0f;
	float m_rockOnSize_3 = 1.0f;
	float m_rockOnSize_4 = 1.0f;
	float m_angle = 0.0f;
};