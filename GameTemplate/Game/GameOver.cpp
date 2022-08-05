#include "stdafx.h"
#include "GameOver.h"

#include "Game.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	m_game = FindGO<Game>("game");

	m_backGround.Init("Assets/sprite/GameOver/BackGround.dds", 1600.0f, 900.0f);
	m_font.Init("Assets/sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);

	return true;
}

void GameOver::Update()
{
	Sprite();

	//Bボタンを押すと
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//タイトルに戻す
		m_game->SetGameState(2);
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
	m_font.Draw(rc);
}

void GameOver::Sprite()
{
	if (m_scale <= 0.05f)
	{
		m_scale += 0.01f;
	}
	else if (m_scale >= 0.05f && m_scale < 1.0f)
	{
		m_scale += 0.1f;
	}

	m_backGround.SetScale({ m_scale,1.0f,1.0f });
	m_font.SetScale({ m_scale,1.0f,1.0f });
	m_backGround.Update();
	m_font.Update();
}