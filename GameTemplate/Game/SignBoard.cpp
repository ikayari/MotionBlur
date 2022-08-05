#include "stdafx.h"
#include "SignBoard.h"

SignBoard::SignBoard()
{

}

SignBoard::~SignBoard()
{

}

bool SignBoard::Start()
{
	m_modelRender.SetDithering(en_pixeldithering);
	m_modelRender.Init("Assets/modelData/Stage_0/Signboard.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void SignBoard::Update()
{
	m_modelRender.Update();
}

void SignBoard::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}