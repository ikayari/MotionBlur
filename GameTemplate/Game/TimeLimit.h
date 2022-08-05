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
	/// �c�莞�Ԃ𑝂₷
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
	/// �t�F�[�h����
	/// </summary>
	void Fade();

	/// <summary>
	/// ���Ԃ̊Ǘ�
	/// </summary>
	void Time();

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
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
	float						m_currentAlpha = 0.0f;		//a�l�B
};

