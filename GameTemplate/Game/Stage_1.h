#pragma once

#include<LevelRender.h>;

class Bumper;
class Drone;
class HoneyCombBlock;
class JumpBoard;
class Nut;
class Player;
class Stage_1_Stage;
class Stage_1_Wall;

class Stage_1 : public IGameObject
{
public:

	Stage_1();
	~Stage_1();
	bool Start();
	void Update();

private:

	LevelRender					m_levelRender;

	//インスタンス
	Stage_1_Stage*				m_stage_1_Stage;
	Stage_1_Wall*				m_stage_1_Wall;
};