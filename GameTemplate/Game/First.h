#pragma once

class Game;
class Title;

/// <summary>
/// �Q�[���ƃ^�C�g����Z�߂�
/// </summary>
class First : public IGameObject
{
public:
	First();
	~First();
	bool Start();
	void Update();

	/// <summary>
	/// �X�e�[�g��ݒ�BTrue�Ń^�C�g�����쐬�B
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