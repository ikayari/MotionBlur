#pragma once

class Game;

/// <summary>
/// ゲームクリア
/// </summary>
class GameClear
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// 画像を管理。
	/// </summary>
	void Sprite();

	SpriteRender	m_backGround;
	SpriteRender	m_font;

	Game*			m_game;

	float			m_scale = 0.0f;
};