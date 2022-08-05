#include "stdafx.h"
#include "Stage_1_Stage.h"

Stage_1_Stage::Stage_1_Stage()
{

}

Stage_1_Stage::~Stage_1_Stage()
{

}

bool Stage_1_Stage::Start()
{
	m_modelRender.SetRecieveShadow(true);
	m_modelRender.Init("Assets/modelData/Stage_0/Stage_1_Ground.tkm");
	m_modelRender.Update();

	return true;
}

void Stage_1_Stage::Update()
{
	m_modelRender.Update();
}

void Stage_1_Stage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}