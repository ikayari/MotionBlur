#pragma once

class Player;

/// <summary>
/// バウンド時のエフェクト
/// </summary>
class Bound :public IGameObject
{
public:

	Bound();
	~Bound();
	bool Start();
	void Update();

private:

	Vector3 m_position;
	EffectEmitter* m_bound;
};