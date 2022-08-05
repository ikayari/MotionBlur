#include "stdafx.h"
#include "GameCamera.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"

namespace
{
	const float FIRST_CAMERA_POSITION = 40.0f;
	const float SET_FAR = 1000000.0f;
	const float SET_SPRING_CAMERA_MAX_SPEED = 100000.0f;
	const Vector3  FIRST_TO_CAMERA_POSITION = { 0.0f,600.0f,500.0f };

	const float	DAMPING_RATE_ON_DASH = 1.75f;			// ロックオンンダッシュ開始時のダンピングレート。
	const float	DAMPING_RATE_ON_NORMAL = 0.5f;			// 通常時のダンピングレート。

	const Vector3 FONT_POSITION = { -500.0f, 250.0f, 0.0f };
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_dampingRate = DAMPING_RATE_ON_NORMAL;
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_toCameraPos.Set(FIRST_TO_CAMERA_POSITION);

	g_camera3D->SetFar(SET_FAR);

	m_springCamera.Refresh();

	m_springCamera.Init
	(
		*g_camera3D,
		SET_SPRING_CAMERA_MAX_SPEED
	);

	m_springCamera.SetDampingRate(DAMPING_RATE_ON_NORMAL);

	Quaternion firstCameraPosition;
	firstCameraPosition.SetRotationDegX(FIRST_CAMERA_POSITION);
	firstCameraPosition.Apply(m_toCameraPos);

	return true;
}

void GameCamera::Render(RenderContext& rc)
{
#ifdef K2_DEBUG
	m_fontRender.Draw(rc);
#endif
}

void GameCamera::NotifyStartDash()
{
	m_dampingRate = DAMPING_RATE_ON_DASH;
}

void GameCamera::Update()
{
	if (m_player->GetIsPressState() == true)
	{
		NotifyStartDash();
		m_player->SetIsPressState(false);
	}

	wchar_t x[256];
	swprintf_s(x, 256, L"rate%f", m_dampingRate);
	m_fontRender.SetText(x);
	m_fontRender.SetPosition(FONT_POSITION);

	m_coolTime += g_gameTime->GetFrameDeltaTime();

	m_target = m_player->GetPosition();
	m_target.y += 0.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	パッドの入力を使ってカメラを回す
	if (m_game->GetGameState() == 0)
	{
		m_rotationX = g_pad[0]->GetRStickXF();
		m_rotationY = g_pad[0]->GetRStickYF();
	}

	else
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
	}

	//	Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 5.0f * m_rotationX);
	qRot.Apply(m_toCameraPos);

	//	X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 5.0f * m_rotationY);
	qRot.Apply(m_toCameraPos);

	//	カメラの回転の上限をチェックする
	//	注視点から視点までのベクトルを正規化する
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		m_toCameraPos = toCameraPosOld;									//	カメラが上に向き過ぎるのを防ぐ
	}
	else if (toPosDir.y > 0.55f) {
		m_toCameraPos = toCameraPosOld;									//	カメラが下に向き過ぎるのを防ぐ
	}

	//	視点を計算する
	Vector3 pos = m_target + m_toCameraPos;

	// ダンピングレートを計算する。
	m_dampingRate += (DAMPING_RATE_ON_NORMAL - m_dampingRate) * 0.03f; // ダンピングレートを徐々に落としていく。
	// DAMPING_RATE_ON_NORMALより小さくならないようにmax関数で補正する。
	m_dampingRate = std::max<float>(m_dampingRate, DAMPING_RATE_ON_NORMAL);

	m_springCamera.SetDampingRate(m_dampingRate);
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);
	m_springCamera.Update();
}