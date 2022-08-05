#pragma once

#include <SpringCamera.h>

class Game;
class Player;
class RockOn;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// ダッシュが開始されたことを通知。
	/// </summary>
	void NotifyStartDash();
	
private:

	FontRender      m_fontRender;

	SpringCamera	m_springCamera;

	Vector3			m_position;
	Vector3			m_target;
	Vector3			m_toCameraPos = Vector3::One;

	Game*			m_game;
	Player*			m_player;
	RockOn*			m_rockOn;

	bool			m_isRockOnJudge = false;
	float			m_rotationX = 0.0f;
	float			m_rotationY = 0.0f;
	float			m_dampingRate = 0.0f;
	float			m_coolTime = 0.0f;
};