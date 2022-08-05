#include "stdafx.h"
#include "Stage_0_Ground.h"

Stage_0_Ground::Stage_0_Ground()
{
	
}

Stage_0_Ground::~Stage_0_Ground()
{

}

bool Stage_0_Ground::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Stage_0_Ground.tkm");
	m_modelRender.Update();

	//m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Stage_0_Ground::Update()
{
	m_modelRender.Update();
}

void Stage_0_Ground::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}