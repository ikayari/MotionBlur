#include "stdafx.h"
#include "RockOn.h"

#include "Bumper.h"
#include "Player.h"

namespace
{
	const float ROCKON_SPRITE_SIZE = 200.0f;
}

RockOn::RockOn()
{

}

RockOn::~RockOn()
{

}

bool RockOn::Start()
{
	m_rockOn_1.Init("Assets/sprite/RockOn/RockOn_1.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_1.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_1.Update();
	m_rockOn_2.Init("Assets/sprite/RockOn/RockOn_2.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_2.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_2.Update();
	m_rockOn_3.Init("Assets/sprite/RockOn/RockOn_3.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_3.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_3.Update();
	m_rockOn_4.Init("Assets/sprite/RockOn/RockOn_4.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_4.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_4.Update();
	m_rockOn_5.Init("Assets/sprite/RockOn/RockOn_5.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_5.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_5.Update();
	m_rockOn_6.Init("Assets/sprite/RockOn/RockOn_6.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_6.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_6.Update();
	m_rockOn_7.Init("Assets/sprite/RockOn/RockOn_7.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_7.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_7.Update();
	m_rockOn_8.Init("Assets/sprite/RockOn/RockOn_8.dds", ROCKON_SPRITE_SIZE, ROCKON_SPRITE_SIZE);
	m_rockOn_8.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_8.Update();

	m_bumper = FindGO<Bumper>("bumper");
	m_player = FindGO<Player>("player");
	m_bumpers = FindGOs<Bumper>("bumper");
	return true;
}

void RockOn::Update()
{
	Judge();
	Sprite();
}

void RockOn::Render(RenderContext& rc)
{
	if (m_isRockOn == true)
	{
		m_rockOn_1.Draw(rc);
		m_rockOn_2.Draw(rc);
		m_rockOn_3.Draw(rc);
		m_rockOn_4.Draw(rc);
		m_rockOn_5.Draw(rc);
		m_rockOn_6.Draw(rc);
		m_rockOn_7.Draw(rc);
		m_rockOn_8.Draw(rc);
	}
}

void RockOn::Judge()
{
	//ロックオン最大距離より大きいベクトルなら何でもいい。
	m_difference = { 10000.0f,10000.0f,10000.0f };

	//一度でも代入されたかどうか。
	bool isInit = false;

	//for文で回す。
	for (auto object : m_rockOnObject)
	{
		if (object->GetState() == 1)
		{
			continue;
		}
		//バンパーとプレイヤーまでの距離。
		Vector3 diff = object->GetPosition() - m_player->GetPosition();
		//遠すぎたり近すぎたら
		if (diff.Length() >= 5000.0f || diff.Length() < 10.0f)
		{
			//ロックオン候補に入らない。
			continue;
		}
		//diffの単位ベクトル。
		Vector3 diffnormal = diff;
		//正規化。
		diffnormal.Normalize();
		//視野角。
		m_angle = acosf(g_camera3D->GetForward().Dot(diffnormal));
		//想定している視野角より大きい場合。
		if (m_angle > (Math::PI / 180.0f) * 35.0f)
		{
			//ロックオン候補に入らない。
			continue;
		}
		if (m_difference.Length() > diff.Length())
		{
			m_difference = diff;
			m_RockOnPosition = object->GetPosition();
			//代入された。
			isInit = true;
		}
	}

	//正規化
	m_difference.Normalize();

	//一度でも代入されていたら。
	if (isInit)
	{
		//ロックオンする
		m_isRockOn = true;
	}
	else
	{
		//ロックオンしない
		m_isRockOn = false;
		m_player->SetIsRockOnFire(false);
		m_rockOnSize_1 = 1.0f;
		m_rockOnSize_2 = 1.0f;
		m_rockOnSize_3 = 1.0f;
		m_rockOnSize_4 = 1.0f;
	}
}

void RockOn::Sprite()
{
	if (m_isRockOn == true)
	{
		g_camera3D->CalcScreenPositionFromWorldPosition(m_2DPosition, m_RockOnPosition);
		m_position.x = m_2DPosition.x;
		m_position.y = m_2DPosition.y;
		m_position.z = 0.0f;

		m_rockOn_1.SetPosition(m_position);
		m_rockOn_2.SetPosition(m_position);
		m_rockOn_3.SetPosition(m_position);
		m_rockOn_4.SetPosition(m_position);
		m_rockOn_5.SetPosition(m_position);
		m_rockOn_6.SetPosition(m_position);
		m_rockOn_7.SetPosition(m_position);
		m_rockOn_8.SetPosition(m_position);

		m_rotation_Num1 += 0.7f;
		m_rotation_Num2 += 1.2f;
		m_rotation_Num3 += 1.3f;
		m_rotation_Num4 += 1.4f;
		m_rotation_Num5 += 1.0f;
		m_rotation_Num6 += 1.6f;
		m_rotation_Num7 += 1.7f;
		m_rotation_Num8 += 1.8f;

		m_rotation_1.SetRotationDegZ(m_rotation_Num1);
		m_rotation_2.SetRotationDegZ(-m_rotation_Num2);
		m_rotation_3.SetRotationDegZ(m_rotation_Num3);
		m_rotation_4.SetRotationDegZ(-m_rotation_Num4);
		m_rotation_5.SetRotationDegZ(m_rotation_Num5);
		m_rotation_6.SetRotationDegZ(-m_rotation_Num6);
		m_rotation_7.SetRotationDegZ(m_rotation_Num7);
		m_rotation_8.SetRotationDegZ(-m_rotation_Num8);

		m_rockOn_1.SetRotation(m_rotation_1);
		m_rockOn_1.Update();
		m_rockOn_2.SetRotation(m_rotation_2);
		m_rockOn_2.Update();
		m_rockOn_3.SetRotation(m_rotation_3);
		m_rockOn_3.Update();
		m_rockOn_4.SetRotation(m_rotation_4);
		m_rockOn_4.Update();
		m_rockOn_5.SetRotation(m_rotation_5);
		m_rockOn_5.Update();
		m_rockOn_6.SetRotation(m_rotation_6);
		m_rockOn_6.Update();
		m_rockOn_7.SetRotation(m_rotation_7);
		m_rockOn_7.Update();
		m_rockOn_8.SetRotation(m_rotation_8);
		m_rockOn_8.Update();

		if (m_rockOnSize_1 >= 0.5)
		{
			m_rockOnSize_1 -= 0.05;
			m_rockOn_1.SetScale(Vector3{ m_rockOnSize_1,m_rockOnSize_1,0.0f });
			m_rockOn_1.Update();
			m_rockOn_2.SetScale(Vector3{ m_rockOnSize_1,m_rockOnSize_1,0.0f });
			m_rockOn_2.Update();
		}
		if (m_rockOnSize_2 >= 0.5)
		{
			m_rockOnSize_2 -= 0.055;
			m_rockOn_3.SetScale(Vector3{ m_rockOnSize_2,m_rockOnSize_2,0.0f });
			m_rockOn_3.Update();
			m_rockOn_4.SetScale(Vector3{ m_rockOnSize_2,m_rockOnSize_2,0.0f });
			m_rockOn_4.Update();
		}
		if (m_rockOnSize_3 >= 0.5)
		{
			m_rockOnSize_3 -= 0.06;
			m_rockOn_5.SetScale(Vector3{ m_rockOnSize_3,m_rockOnSize_3,0.0f });
			m_rockOn_5.Update();
			m_rockOn_6.SetScale(Vector3{ m_rockOnSize_3,m_rockOnSize_3,0.0f });
			m_rockOn_6.Update();
		}
		if (m_rockOnSize_4 >= 0.5)
		{
			m_rockOnSize_4 -= 0.065;
			m_rockOn_7.SetScale(Vector3{ m_rockOnSize_4,m_rockOnSize_4,0.0f });
			m_rockOn_7.Update();
			m_rockOn_8.SetScale(Vector3{ m_rockOnSize_4,m_rockOnSize_4,0.0f });
			m_rockOn_8.Update();
		}
	}
}
