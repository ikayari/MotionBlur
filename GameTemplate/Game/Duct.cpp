#include "stdafx.h"
#include "Duct.h"

Duct::Duct()
{

}

Duct::~Duct()
{

}

bool Duct::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Duct.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	return true;
}

void Duct::Update()
{
	m_modelRender.Update();
}

void Duct::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}