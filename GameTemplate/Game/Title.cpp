#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Setting.h"

namespace
{
	const float FONT_SIZE = 200.0f;
	const float LOGO_SIZE = 40.0f;

	const float CHOISE_SOUND_SIZE = 0.3f;
}

Title::Title()
{

}

Title::~Title()
{
	
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");

	m_backGround.Init("Assets/sprite/Title/TitleBackGround.dds", 1600.0f, 900.0f);

	m_start.Init("Assets/sprite/Title/Start.dds", FONT_SIZE, FONT_SIZE);
	m_start.SetPosition({ 0.0f,-200.0f,0.0f });
	m_start.Update();
	m_startBlack.Init("Assets/sprite/Title/StartBlack.dds", FONT_SIZE, FONT_SIZE);
	m_startBlack.SetPosition({ 0.0f,-200.0f,0.0f });
	m_startBlack.Update();
	m_startLogo.Init("Assets/sprite/Title/StartLogo.dds", LOGO_SIZE, LOGO_SIZE);
	m_startLogo.SetPosition({ -130.0f,-200.0f,0.0f });
	m_startLogo.Update();
	m_startLogoBlack.Init("Assets/sprite/Title/StartLogoBlack.dds", LOGO_SIZE, LOGO_SIZE);
	m_startLogoBlack.SetPosition({ -130.0f,-200.0f,0.0f });
	m_startLogoBlack.Update();
	m_startBack.Init("Assets/sprite/Title/StartBack.dds", 300.0f, 300.0f);
	m_startBack.SetPosition({ -30.0f,-200.0f,0.0f });
	m_startBack.Update();
	m_setting.Init("Assets/sprite/Title/Setting.dds", FONT_SIZE, FONT_SIZE);
	m_setting.SetPosition({ 0.0f,-250.0f,0.0f });
	m_setting.Update();
	m_settingBlack.Init("Assets/sprite/Title/SettingBlack.dds", FONT_SIZE, FONT_SIZE);
	m_settingBlack.SetPosition({ 0.0f,-250.0f,0.0f });
	m_settingBlack.Update();
	m_settingLogo.Init("Assets/sprite/Title/SettingLogo.dds", LOGO_SIZE, LOGO_SIZE);
	m_settingLogo.SetPosition({ -130.0f,-250.0f,0.0f });
	m_settingLogo.Update();
	m_settingLogoBlack.Init("Assets/sprite/Title/SettingLogoBlack.dds", LOGO_SIZE, LOGO_SIZE);
	m_settingLogoBlack.SetPosition({ -130.0f,-250.0f,0.0f });
	m_settingLogoBlack.Update();
	m_settingBack.Init("Assets/sprite/Title/SettingBack.dds", 300.0f, 300.0f);
	m_settingBack.SetPosition({ -30.0f,-250.0f,0.0f });
	m_settingBack.Update();

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");
	
	return true;
}

void Title::Update()
{
	//スタートにカーソルがあっている時
	if (m_choiceState == 0 && g_pad[0]->IsTrigger(enButtonB))
	{
		m_game->SetGameState(0);
		DeleteGO(this);
	}
	//スタートにカーソルがあっている時
	if (m_choiceState == 1 && g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Setting>(0, "setting");
		DeleteGO(this);
	}
	Back();
	Choice();
}

void Title::Render(RenderContext& rc)
{
	//背景
	m_backGround.Draw(rc);

	//選択背景
	if (m_choiceState == 0)
	{
		m_setting.Draw(rc);
		m_settingLogo.Draw(rc);

		m_startBack.Draw(rc);
		m_startBlack.Draw(rc);
		m_startLogoBlack.Draw(rc);
	}
	
	if (m_choiceState == 1)
	{
		m_start.Draw(rc);
		m_startLogo.Draw(rc);

		m_settingBack.Draw(rc);
		m_settingBlack.Draw(rc);
		m_settingLogoBlack.Draw(rc);
	}
}

void Title::Back()
{
	if (m_backCharge >= 0 && m_backCharge < 1)
	{
		m_backCharge += 0.05;
	}

	m_startBack.SetIsDisplayRestrictionRightSide(true);
	m_startBack.SetLimitedX(m_backCharge);

	m_settingBack.SetIsDisplayRestrictionRightSide(true);
	m_settingBack.SetLimitedX(m_backCharge);
}

void Title::Choice()
{
	if (m_choiceState >= 0 && m_choiceState < 1 && g_pad[0]->IsTrigger(enButtonDown))
	{
		m_backCharge = 0;
		m_choiceState += 1;
		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(CHOISE_SOUND_SIZE);
		m_choiceSE->Play(false);
	}

	if (m_choiceState <= 1 && m_choiceState > 0 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_backCharge = 0;
		m_choiceState -= 1;
		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(CHOISE_SOUND_SIZE);
		m_choiceSE->Play(false);
	}
}