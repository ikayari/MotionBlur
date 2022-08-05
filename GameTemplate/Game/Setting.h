#pragma once

class First;
class Title;

/// <summary>
/// İ’è‰æ–Ê
/// </summary>
class Setting : public IGameObject
{
public:

	Setting();
	~Setting();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// ‘I‘ğ‚ÌŠÇ—B
	/// </summary>
	void Choice();

	/// <summary>
	/// ‰æ‘œ‚ğŠÇ—B
	/// </summary>
	void Sprite();

	FontRender      m_fontRender;

	SoundSource*	m_choiceSE;

	SpriteRender	m_apply;
	SpriteRender	m_applyChoice;
	SpriteRender	m_backGround;
	SpriteRender	m_cancel;
	SpriteRender	m_cancelChoice;
	SpriteRender	m_controll;
	SpriteRender	m_controllChoice;
	SpriteRender	m_sound;
	SpriteRender	m_soundChoice;
	SpriteRender	m_stickSensitivity;
	SpriteRender	m_stickSensitivityChoice;
	SpriteRender	m_stickSensitivityBar;
	SpriteRender	m_stickSensitivityBarChoice;
	SpriteRender	m_stickSensitivityBarInside;
	SpriteRender	m_stickSensitivityBarInsideChoice;
	SpriteRender	m_vibration;
	SpriteRender	m_vibrationChoice;

	First*			m_first;
	Title*			m_title;

	int				m_shelf = 0;
	int				m_choiceState = 0;
	float			m_stickSensitivityNum = 5.0f;

	float			m_scale = 0;

	bool			m_stickSensitivityUp = false;
	bool			m_stickSensitivityDown = false;
};