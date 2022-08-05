#pragma once

class Game;

/// <summary>
/// タイトル
/// </summary>
class Title : public IGameObject
{
public:

	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	void Back();
	/// <summary>
	/// 選択の管理。
	/// </summary>
	void Choice();

	SoundSource*	m_choiceSE;
	
	SpriteRender	m_backGround;
	SpriteRender	m_start;
	SpriteRender	m_startBlack;
	SpriteRender	m_startLogo;
	SpriteRender	m_startLogoBlack;
	SpriteRender	m_startBack;
	SpriteRender	m_setting;
	SpriteRender	m_settingBlack;
	SpriteRender	m_settingLogo;
	SpriteRender	m_settingLogoBlack;
	SpriteRender	m_settingBack;

	Game*			m_game;

	int				m_choiceState = 0;

	float			m_backCharge = 0.0f;
};