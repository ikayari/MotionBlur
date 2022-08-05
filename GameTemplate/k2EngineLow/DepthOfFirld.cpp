#include "k2EngineLowPreCompile.h"
#include "DepthOfFirld.h"

namespace nsK2EngineLow {

	DepthOfField g_depthOfField;

	void DepthOfField::Init()
	{
		//�K�E�V�A���u���[���쐬
		GaussianBlur blur;
		blur.Init(&g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture());

		//�����p�̃{�P���摜���쐬
		SpriteInitData combineBokeSpriteInitData;

		//�e�N�X�`����񖇍쐬
		combineBokeSpriteInitData.m_textures[0] = &blur.GetBokeTexture();
		combineBokeSpriteInitData.m_textures[1] = &g_renderingEngine.GetDepthRenderTarget().GetRenderTargetTexture();
		combineBokeSpriteInitData.m_width = 1600;
		combineBokeSpriteInitData.m_height = 900;

		//�t�@�C���p�X���w��
		combineBokeSpriteInitData.m_fxFilePath = "Assets/shader/Dof.fx";
		combineBokeSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		combineBokeSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		Sprite combineBokeSprite;
		combineBokeSprite.Init(combineBokeSpriteInitData);

		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture();

		//�t���[���o�b�t�@�ɍ�������̂ŉ𑜓x�͓����ɂ���
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;

		//�ʏ퍇������
		spriteInitData.m_fxFilePath = "Assets/shader/";

		//�摜��������
		Sprite copyToFrameBufferSprite;
		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void DepthOfField::Render(RenderContext& rc)
	{
	}
}