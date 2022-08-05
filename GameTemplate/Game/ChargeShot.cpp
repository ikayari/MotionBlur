#include "stdafx.h"
#include "ChargeShot.h"

#include "Game.h"
#include "Player.h"

namespace
{
	//画像
	const Vector3 CHARGE_2D_POSITION = { -400.0f, -250.0f, 0.0f };
	const Vector3 CHARGE_INSIDE_2D_POSITION = { -295.0f, -288.0f, 0.0f };
	
	//フォント
	const Vector3 FONT_SIZE = { -630.0f, -330.0f, 0.0f };
	const Vector3 FONT_COLOR = { 0.0f, 230.0f, 255.0f };
}

ChargeShot::ChargeShot()
{

}

ChargeShot::~ChargeShot()
{

}

bool ChargeShot::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_charge2D.Init("Assets/sprite/Charge/Charge.dds", 700.0f, 700.0f);
	m_charge2D.SetPosition(CHARGE_2D_POSITION);
	m_charge2D.Update();

	m_chargeInside2D.Init("Assets/sprite/Charge/ChargeInside.dds", 315.0f, 315.0f);
	m_chargeInside2D.SetPosition(CHARGE_INSIDE_2D_POSITION);
	m_chargeInside2D.Update();

	m_fontRender.SetScale(2.0f);
	m_fontRender.SetPivot(1.0f, 0.5f);
	m_fontRender.SetPosition(FONT_SIZE);

	return true;
}

void ChargeShot::Update()
{
	Cut();
	Fade();
	Speed();
	m_charge2D.Update();
	m_chargeInside2D.Update();
}

void ChargeShot::Render(RenderContext& rc)
{
	//ゲームが始まってなかったら
	if (m_game->GetGameState() == 0)
	{
		m_fadeState = enState_FadeOut;

		m_charge2D.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_charge2D.Draw(rc);

		m_chargeInside2D.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_chargeInside2D.Draw(rc);

		m_fontRender.SetColor({ FONT_COLOR.x, FONT_COLOR.y, FONT_COLOR.z, m_currentAlpha });
		m_fontRender.Draw(rc);
	}
}

void ChargeShot::Fade()
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

void ChargeShot::Cut()
{
	m_chargeInside2D.SetIsDisplayRestrictionRightSide(true);
	m_chargeInside2D.SetLimitedX(m_player->GetCharge());
}

void ChargeShot::Speed()
{
	m_speed = m_player->GetPlayerSpeed();

	if (m_game->GetGameState() == 0)
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%03d", int(m_speed * 60 / 1000));
		m_fontRender.SetText(wcsbuf);
	}
	else
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%03d", int(0));
		m_fontRender.SetText(wcsbuf);
	}
}