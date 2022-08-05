#include "stdafx.h"
#include "Volt.h"

Volt::Volt()
{

}

Volt::~Volt()
{

}

bool Volt::Start()
{
	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Volt.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Volt::Update()
{
	m_modelRender.Update();
}

void Volt::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}