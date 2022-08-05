/*!
 * @brief �V���h�E�}�b�v�`��p�̃V�F�[�_�[
 */

 // ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//�X�L�j���O�p�̒��_�f�[�^���ЂƂ܂Ƃ߁B
struct SSkinVSIn {
    int4   Indices  : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION; // ���f���̒��_���W
    SSkinVSIn skinVert;				//�X�L���p�̃f�[�^�B
};

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_POSITION; // �X�N���[����Ԃł̃s�N�Z���̍��W
};

///////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//�{�[���s��B

////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////

/// <summary>
//�X�L���s����v�Z����B
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}
/// <summary>
/// ���_�V�F�[�_�[
/// <summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin) {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else {
        m = mWorld;
    }
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    return psIn;
}
/// <summary>
/// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}
/// <summary>
/// �V���h�E�}�b�v�`��p�̃s�N�Z���V�F�[�_�[
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // step-5 �V���h�E�}�b�v�`��p�̃s�N�Z���V�F�[�_�[���쐬����
    return float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
}