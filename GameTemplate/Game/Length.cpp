#include "stdafx.h"
#include "Length.h"

#include "Game.h"
#include "Goal.h"

namespace
{
	const Vector3 SET_COLOR = { 0.0f,230.0f,255.0f };                       //フォントのカラー
	const float GOAL_LENGTH = 181038.531f;
}

Length::Length()
{

}

Length::~Length()
{

}

bool Length::Start()
{
	m_game = FindGO<Game>("game");
	m_goal = FindGO<Goal>("goal");

	m_length2D.Init("Assets/sprite/Length/Length.dds", 700.0f, 700.0f);
	m_length2D.SetPosition(Vector3(400.0f, -250.0f, 0.0f));
	m_length2D.Update();

	m_lengthInside2D.Init("Assets/sprite/Length/ChargeInside.dds", 315.0f, 315.0f);
	m_lengthInside2D.SetPosition(Vector3(295.0f, -288.0f, 0.0f));
	m_lengthInside2D.Update();

	m_fontRender.SetScale(2.0f);
	m_fontRender.SetPivot(1.0f, 0.5f);
	m_fontRender.SetPosition({ 630.0f, -330.0f, 0.0f });

	return true;
}

void Length::Update()
{
	Cut();
	Fade();
	LengthFont();
	m_length2D.Update();
	m_lengthInside2D.Update();
}

void Length::Render(RenderContext& rc)
{
	//ゲームが始まってなかったら
	if (m_game->GetGameState() == 0)
	{
		m_fadeState = enState_FadeOut;

		m_length2D.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_length2D.Draw(rc);

		m_lengthInside2D.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_lengthInside2D.Draw(rc);

		m_fontRender.SetColor({ SET_COLOR.x, SET_COLOR.y, SET_COLOR.z, m_currentAlpha });
		m_fontRender.Draw(rc);
	}
}

void Length::Fade()
{
	switch (m_fadeState) {
	case enState_FadeIn:
		m_currentAlpha -= g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_fadeState = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_fadeState = enState_Idle;
		}
		break;
	case enState_Idle:
		break;
	}
}

void Length::Cut()
{
	//プレイヤーとゴールの直線距離を代入
	m_length = m_goal->GetLength();

	m_lengthInside2D.SetIsDisplayRestrictionLeftSide(true);
	m_lengthInside2D.SetLimitedX(1.0-(m_length / GOAL_LENGTH));
}

void Length::LengthFont()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%03d", int(m_length/1000));

	m_fontRender.SetText(wcsbuf);

	//フォントの位置を設定。
	m_fontRender.SetPosition({ 775.0f, -330.0f, 0.0f });

	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ SET_COLOR.x, SET_COLOR.y, SET_COLOR.z,0.0f });
	m_fontRender.SetPivot(1.0f, 0.5f);
}