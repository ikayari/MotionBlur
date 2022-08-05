#pragma once

class Bound;
class ChargeShot;
class First;
class GameCamera;
class GameLight;
class Length;
class Player;
class PowerCharge;
class RockOn;
class SonicBoom;
class Stage_1;
class Title;
class TimeLimit;
class Window;

class Game : public IGameObject
{
public:

	Game();
	~Game();
	bool Start() override;
	void Update() override;

	/// <summary>
	/// �Q�[���̃X�e�[�g���Ǘ��B1�͑���s�\�B2�̓Q�[���I���B
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	void SetGameState(const int& state)
	{
		m_state = state;
	}

	/// <summary>
	/// �X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	int GetGameState() const
	{
		return m_state;
	}

private:

	/// <summary>
	/// ���S�̔���
	/// </summary>
	void Death();

	SoundSource*			m_backGroundBGM;
	Bound*					m_bound;
	ChargeShot*				m_chargeShot;
	First*					m_first;
	GameCamera*				m_gameCamera;
	GameLight*				m_gameLight;
	Length*					m_length;
	Player*					m_player;
	PowerCharge*			m_powerCharge;
	RockOn*					m_rockOn;
	SonicBoom*				m_sonicBoom;
	Stage_1*				m_stage_1;
	TimeLimit*				m_timeLimit;
	Window*					m_window;

	int						m_state = 1;
};