#pragma once

class Player;

/// <summary>
/// パワーチャージ
/// </summary>
class PowerCharge : public IGameObject
{
public:

	PowerCharge();
	~PowerCharge();
	bool Start();
	void Update();

private:

	Vector3						m_position;

	EffectEmitter*				m_powerCharge;
	SoundSource*				m_powerChargeSE;
	Player*						m_player;

	float						m_aliveTimer = 0.0f;
};