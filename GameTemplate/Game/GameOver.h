#pragma once

class Game;

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
class GameOver : public IGameObject
{
public:

	GameOver();
	~GameOver();
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