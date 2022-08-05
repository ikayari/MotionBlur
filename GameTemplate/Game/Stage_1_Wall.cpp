#include "stdafx.h"
#include "Stage_1_Wall.h"

Stage_1_Wall::Stage_1_Wall()
{

}

Stage_1_Wall::~Stage_1_Wall()
{

}

bool Stage_1_Wall::Start()
{
	m_modelRender.SetDithering(en_pixeldithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Stage_1_Wall.tkm");
	m_modelRender.Update();

	return true;
}

void Stage_1_Wall::Update()
{
	m_modelRender.Update();
}

void Stage_1_Wall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}