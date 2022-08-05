#include "k2EngineLowPreCompile.h"
#include "MotionBlur.h"
namespace nsK2EngineLow
{
	void MotionBlur::InitBlurSprite()
	{
		
		//�����������쐬����B
		SpriteInitData motionBlurSpriteData;
		//�u���[�p�̃V�F�[�_�[�B
		motionBlurSpriteData.m_fxFilePath = "Assets/shader/MotionBlur.fx";
		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		motionBlurSpriteData.m_vsEntryPointFunc = "VSMain";
		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		motionBlurSpriteData.m_psEntryPoinFunc = "PSMain";
		//�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ����B
		motionBlurSpriteData.m_width = 1600;
		motionBlurSpriteData.m_height = 900;
		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�B
		motionBlurSpriteData.m_textures[0] = &g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture();
		motionBlurSpriteData.m_textures[1] = &g_renderingEngine.GetvelocityRenderTarget().GetRenderTargetTexture();
		//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
		motionBlurSpriteData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		motionBlurSpriteData.m_alphaBlendMode = AlphaBlendMode_None;

		//�쐬�����������������ƂɃX�v���C�g������������B

		m_motionBlurSprite.Init(motionBlurSpriteData);
	}
	void MotionBlur::Render(RenderContext& rc)
	{
		m_motionBlurSprite.Draw(rc);
	}
}