#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow {

	PostEffect g_postEffect;

	void PostEffect::Init()
	{

		m_motionBlur.InitBlurSprite();
		//�𑜓x�A�~�b�v�}�b�v���x��
		luminanceRenderTarget.Create(
			1600,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			900,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			1,
			1,
			//�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

	}

	void PostEffect::Render(RenderContext& rc)
	{
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.luminanceRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTarget(g_postEffect.luminanceRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(g_postEffect.luminanceRenderTarget);

		g_bloom.LuminanceSpriteDraw(rc);

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.luminanceRenderTarget);

		g_bloom.Blur(rc);

		g_bloom.Render(rc, g_renderingEngine.GetmainRenderTarget());
		// step-5 ��ʂɕ\������郌���_�����O�^�[�Q�b�g�ɖ߂�
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		g_bloom.Draw(rc);
		m_motionBlur.Render(rc);
		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &g_renderingEngine.GetvelocityRenderTarget().GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		Sprite spsp;
		spsp.Init(spriteInitData);
		if (g_pad[0]->IsPress(enButtonSelect))
		{
			spsp.Draw(rc);
		}
	}
	void PostEffect::MotionBlurDraw(RenderContext& rc)
	{
		m_motionBlur.Render(rc);
	}
}