#pragma once

class Game;

/// <summary>
/// チャージゲージ
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
	/// フェード処理
	/// </summary>
	void Fade();

	enum EnState {
		enState_FadeIn,			//フェードイン中。
		enState_FadeOut,		//フェードアウト中。
		enState_Idle,			//アイドル中。
	};
	EnState			m_fadeState;

	//画像
	SpriteRender	m_window2D;

	Game*			m_game;

	float			m_currentAlpha = 0.0f;		//a値。
};