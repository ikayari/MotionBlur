#include "stdafx.h"
#include "GameLight.h"

GameLight::GameLight()
{

}

GameLight::~GameLight()
{

}

bool GameLight::Start()
{
	g_sceneLight.SetDirectionColor({ 0.5f,0.5f,0.7f });
	return true;
}

void GameLight::Update()
{

}