#pragma once

class Game;
class Title;

/// <summary>
/// ゲームとタイトルを纏める
/// </summary>
class First : public IGameObject
{
public:
	First();
	~First();
	bool Start();
	void Update();

	/// <summary>
	/// ステートを設定。Trueでタイトルを作成。
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	bool SetIsCreate(const bool& value)
	{
		m_isCreate = value;
		return 0;
	}
private:

	Game*		m_game;
	Title*		m_title;

	bool		m_isCreate = true;
};