#include "stdafx.h"
#include "HoneyCombBlock.h"

HoneyCombBlock::HoneyCombBlock()
{

}

HoneyCombBlock::~HoneyCombBlock()
{

}

bool HoneyCombBlock::Start()
{
	m_modelRender.SetDithering(en_dithering);
	m_modelRender.Init("Assets/modelData/Stage_0/HoneyCombBlock.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.5);

	return true;
}

void HoneyCombBlock::Update()
{
	m_modelRender.Update();
}

void HoneyCombBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}