#include "stdafx.h"
#include "Window.h"

#include "Game.h"

Window::Window()
{

}

Window::~Window()
{

}

bool Window::Start()
{
	m_game = FindGO<Game>("game");

	m_window2D.Init("Assets/sprite/window/UI.dds",1600.0f, 900.0f);

	return true;
}

void Window::Update()
{
	Fade();
}

void Window::Render(RenderContext& rc)
{
	//ƒQ[ƒ€‚ªŽn‚Ü‚Á‚Ä‚È‚©‚Á‚½‚ç•`‰æ‚µ‚È‚¢
	if (m_game->GetGameState() == 0)
	{
		m_fadeState = enState_FadeOut;
		m_window2D.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_window2D.Draw(rc);
	}
}

void Window::Fade()
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