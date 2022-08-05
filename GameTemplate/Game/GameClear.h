#pragma once

class Game;

/// <summary>
/// �Q�[���N���A
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
	/// �摜���Ǘ��B
	/// </summary>
	void Sprite();

	SpriteRender	m_backGround;
	SpriteRender	m_font;

	Game*			m_game;

	float			m_scale = 0.0f;
};