#pragma once

class Game;

/// <summary>
/// �`���[�W�Q�[�W
/// </summary>
class Window : public IGameObject
{
public:

	Window();
	~Window();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// �t�F�[�h����
	/// </summary>
	void Fade();

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
	};
	EnState			m_fadeState;

	//�摜
	SpriteRender	m_window2D;

	Game*			m_game;

	float			m_currentAlpha = 0.0f;		//a�l�B
};