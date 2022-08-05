#pragma once

#include <SerialNumberSpriteRender.h>

class Game;
class GameOver;

class TimeLimit : public IGameObject
{
public:

	TimeLimit();
	~TimeLimit();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 残り時間を増やす
	/// </summary>
	/// <param name="addTime"></param>
	void AddTime(const float addTime)
	{
		m_limitTimer += addTime;
		m_isSetScale = true;
		m_fontYPosition = 30.0f;
	}

private:

	/// <summary>
	/// フェード処理
	/// </summary>
	void Fade();

	/// <summary>
	/// 時間の管理
	/// </summary>
	void Time();

	enum EnState {
		enState_FadeIn,			//フェードイン中。
		enState_FadeOut,		//フェードアウト中。
		enState_Idle,			//アイドル中。
	};
	EnState						m_fadeState;

	SerialNumberSpriteRender	m_2dAnimation;

	FontRender					m_fontRender;

	Game*						m_game;
	GameOver*					m_gameOver;

	bool						m_isRed;
	bool						m_isSetScale = false;

	float						m_fontYPosition = 30.0f;
	float						m_limitTimer = 0.0f;
	float						m_currentAlpha = 0.0f;		//a値。
};

