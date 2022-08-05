#include "stdafx.h"
#include "Game.h"

#include "Bound.h"
#include "ChargeShot.h"
#include "First.h"
#include "GameCamera.h"
#include "GameLight.h"
#include "Length.h"
#include "Player.h"
#include "PowerCharge.h"
#include "RockOn.h"
#include "Stage_1.h"
#include "TimeLimit.h"
#include "Window.h"

Game::Game()
{

}

Game::~Game()
{
	m_backGroundBGM->Stop();

	//エフェクト
	const auto& bounds = FindGOs<Bound>("bound");
	int buondSize = bounds.size();
	for (int i = 0; i < buondSize; i++)
	{
		DeleteGO(bounds[i]);
	}
	const auto& powerChages = FindGOs<PowerCharge>("powerCharge");
	int powerChargeSize = powerChages.size();
	for (int i = 0; i < powerChargeSize; i++)
	{
		DeleteGO(powerChages[i]);
	}
	const auto& rockOns = FindGOs<RockOn>("rockOn");
	int rockOnSize = rockOns.size();
	for (int i = 0; i < rockOnSize; i++)
	{
		DeleteGO(rockOns[i]);
	}
	DeleteGO(m_chargeShot);
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameLight);
	DeleteGO(m_length);
	DeleteGO(m_player);
	DeleteGO(m_stage_1);
	DeleteGO(m_timeLimit);
	DeleteGO(m_window);
}

bool Game::Start()
{
	DeleteGO(m_first);

	m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_gameLight = NewGO<GameLight>(0, "gameLight");
	m_player = NewGO<Player>(0, "player");
	m_rockOn = NewGO<RockOn>(0, "rockOn");
	m_stage_1 = NewGO<Stage_1>(0, "stage_1");
	m_length = NewGO<Length>(0, "length");
	m_timeLimit = NewGO<TimeLimit>(0, "timeLimit");
	m_window = NewGO<Window>(0, "window");

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/BackGround.wav");
	m_backGroundBGM = NewGO<SoundSource>(12);
	m_backGroundBGM->Init(12);
	m_backGroundBGM->SetVolume(0.1f);
	m_backGroundBGM->Play(true);

	

	return true;
}

void Game::Update()
{
	g_renderingEngine.SetPlayerPosition(m_player->GetPosition());
	Death();
}

void Game::Death()
{
	if (m_state == 2)
	{
		m_state = 1;
		DeleteGO(this);
		m_first = NewGO<First>(0, "first");
	}
}