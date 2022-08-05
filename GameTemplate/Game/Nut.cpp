#include "stdafx.h"
#include "Nut.h"

Nut::Nut()
{

}

Nut::~Nut()
{

}

bool Nut::Start()
{
	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Nut.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Nut::Update()
{
	m_modelRender.Update();
}

void Nut::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}