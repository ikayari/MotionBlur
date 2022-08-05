#include "stdafx.h"
#include "Player.h"

#include "BreakBox.h"
#include "Bumper.h"
#include "Game.h"
#include "GameCamera.h"
#include "PowerCharge.h"
#include "RockOn.h"

namespace
{
    //�v���C���[
    const Vector3 PLAYER_FIRST_POSITION = { 0.0f,250.0f,0.0f };             //�X�|�[�����W
    const float PLAYER_MODEL_SCALE = 1.0f;                                  //�T�C�Y
    const float PLAYER_COLLISION_SCALE = 50.0f;                             //�����蔻��̃T�C�Y
    const float PLAYER_GRAVITY = -200000.0f;                                //�d��
    const float PLAYER_ROLL = 1.0f;                                         //�]����₷��
    const float PLAYER_FRICTION = 1.0f;                                     //���C��
    const float PLAYER_SPEED_DECREASE = 0.997;                              //�X�s�[�h�̌�����
    const float PLAYER_SPEED_DEFAULT = 50000000.0f;                         //�X�s�[�h�f�t�H���g
    const float PLAYER_SPEED_MAX = 10000.0f;                                //�X�s�[�h����l

    //�`���[�W
    const float CHARGE_DEFAULT = 0.0f;                                      //s�`���[�W���Z�b�g�l
    const float CHARGE_ADD = 0.05f;                                         //1f���Ƀ`���[�W�����l

    //�G�t�F�N�g
    const float EFFECT_RESPWAN_SIZE = 3.0f;                                 //���X�|�[���G�t�F�N�g�̃T�C�Y
    const float EFFECT_FIRE_IMPACT_SIZE = 50.0f;                            //���ˎ��̃G�t�F�N�g�̃T�C�Y
}

bool Player::Start()
{
    m_breakBox = FindGO<BreakBox>("breakBox");
    m_bumper = FindGO<Bumper>("bumper");
    m_game = FindGO<Game>("game");
    m_gameCamera = FindGO<GameCamera>("gameCamera");
    m_rockOn = FindGO<RockOn>("rockOn");
    
    m_reSpawnPosition = PLAYER_FIRST_POSITION;
    m_position = PLAYER_FIRST_POSITION;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.SetCasterShadow(true);
    m_modelRender.Init("Assets/modelData/Stage_0/Player.tkm");
    m_modelRender.SetPosition(m_position);

    //�G�t�F�N�g
    EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Selfmade/PowerCharge.efk");
    m_reSpawnEF = NewGO<EffectEmitter>(2);
    m_reSpawnEF->Init(2);
    m_reSpawnEF->SetScale(Vector3::One * EFFECT_RESPWAN_SIZE);
    m_reSpawnEF->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z });

    EffectEngine::GetInstance()->ResistEffect(10, u"Assets/Effect/Selfmade/FireImpact.efk");
    m_fireImpactEF = NewGO<EffectEmitter>(10);
    m_fireImpactEF->Init(10);
    m_fireImpactEF->SetScale(Vector3::One * 300.0f);
    m_fireImpactEF->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z });

    EffectEngine::GetInstance()->ResistEffect(22, u"Assets/Effect/Selfmade/Death.efk");

    //�T�E���h
    g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Shot.wav");
    g_soundEngine->ResistWaveFileBank(15, "Assets/sound/ReSpawn.wav");
    g_soundEngine->ResistWaveFileBank(22, "Assets/sound/Death.wav");

    //�R���C�_�[���������B
    m_sphereCollider.Create(PLAYER_COLLISION_SCALE);

    //���̂��������B
    RigidBodyInitData rbInitData;
    //����(�d��)��ݒ肷��B
    rbInitData.mass = 30.0f;
    //�R���C�_�[��ݒ肷��B
    rbInitData.collider = &m_sphereCollider;
    //���W��ݒ肷��B
    rbInitData.pos = m_position;
    //��]�̂��₷����ݒ肷��B0�`1
    rbInitData.localInteria.Set(
        0.5f,
        0.5f,
        0.5f
    );
    //�����͂�ݒ肷��B
    //���l��傫������ƁA���˕Ԃ肪�傫���Ȃ�B
    //PhysicsStaticObject�ɂ������͂�ݒ肷��K�v������(Game.cpp�Q��)�B
    rbInitData.restitution = 1.0f;
    //���̂��������B
    m_rigidBody.Init(rbInitData);
    //���C�͂�ݒ肷��B0�`10�܂ŁB
    m_rigidBody.SetFriction(PLAYER_FRICTION);
    //���`�ړ�����v�f��ݒ肷��B
    //0���w�肵�����͈ړ����Ȃ��B
    //�Ⴆ��y��0�Ɏw�肷��ƁAy���W�͈ړ����Ȃ��Ȃ�B
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

    return true;
}

void Player::Update()
{
    Move();
    //���f���̍X�V�����B
    m_modelRender.Update();

    //�f�o�b�O�p
    wchar_t x[256];
    swprintf_s(x, 256, L"X=%f", m_position.x);
    m_fontRenderX.SetText(x);
    m_fontRenderX.SetPosition({ 500.0f, 300.0f, 0.0f });
    wchar_t y[256];
    swprintf_s(y, 256, L"Y=%f", m_position.y);
    m_fontRenderY.SetText(y);
    m_fontRenderY.SetPosition({ 500.0f, 250.0f, 0.0f });
    wchar_t z[256];
    swprintf_s(z, 256, L"Z=%f", m_position.z);
    m_fontRenderZ.SetText(z);
    m_fontRenderZ.SetPosition({ 500.0f, 200.0f, 0.0f });

    float time = g_gameTime->GetFrameDeltaTime();
    wchar_t text[256];
    swprintf(text, L"FPS = %0.2f", 1.0f / time);

    m_fpsFont.SetText(text);
}

void Player::UpdateOnStop()
{

}

void Player::Render(RenderContext& rc)
{
    //���f���̕`��B
    if (m_game->GetGameState() == 0 && m_state == 0)
    {
        m_modelRender.Draw(rc);
    }
#ifdef K2_DEBUG
    m_fontRenderX.Draw(rc);
    m_fontRenderY.Draw(rc);
    m_fontRenderZ.Draw(rc);
    m_fpsFont.Draw(rc);
#endif
}

void Player::Death()
{
    m_deathTime += g_gameTime->GetFrameDeltaTime();

    if (m_isEffectStart == true)
    {
        //�G�t�F�N�g
        m_deathEF = NewGO<EffectEmitter>(22);
        m_deathEF->Init(22);
        m_deathEF->SetScale(Vector3::One * 20.0f);
        m_deathEF->Play();

        //�T�E���h
        m_reSpawnSE = NewGO<SoundSource>(22);
        m_reSpawnSE->Init(22);
        m_reSpawnSE->SetVolume(0.2f);
        m_reSpawnSE->Play(false);

        m_isEffectStart = false;
    }

    m_deathEF->SetPosition(m_position);

    if (m_deathTime >= 1.0f)
    {
        ReSpawn();
        m_deathTime = 0.0f;
        m_isEffectStart = true;
    }
}

void Player::ReSpawn()
{
    m_position = m_reSpawnPosition;
    m_rigidBody.SetPositionAndRotation(m_position, m_rotation);
    m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });
    m_isRockOnFire = false;
    m_scale = 0.0f;

    //�G�t�F�N�g
    m_reSpawnEF = NewGO<EffectEmitter>(2);
    m_reSpawnEF->Init(2);
    m_reSpawnEF->SetScale(Vector3::One * EFFECT_RESPWAN_SIZE);
    m_reSpawnEF->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z });
    m_reSpawnEF->Play();

    //�T�E���h
    m_reSpawnSE = NewGO<SoundSource>(15);
    m_reSpawnSE->Init(15);
    m_reSpawnSE->SetVolume(0.175f);
    m_reSpawnSE->Play(false);

    //�o�C�u���[�V����
    g_pad[0]->SetVibration(0.3f, 0.05f);

    g_camera3D->SetPosition(m_position);
    g_camera3D->SetTarget(m_position);
    m_state = 0;
}

void Player::Move()
{
    //�Q�[���X�e�[�g��1(�s���s�\)��������
    if (m_game->GetGameState() != 0)
    {
        //�������^�[��
        m_rigidBody.SetLinearVelocity(Vector3::Zero);
        return;
    }

    if (m_scale <= 1.0f)
    {
        m_scale += 0.1;
    }
    m_modelRender.SetScale(Vector3::One * m_scale);

    //���̂̍��W�Ɖ�]���擾�B
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);

    //���̂̍��W�Ɖ�]�����f���ɔ��f�B
    m_modelRender.SetPosition(m_position);
    Matrix cameraRotationMatrix = g_camera3D->GetCameraRotation();
    m_rotation.SetRotation(cameraRotationMatrix);
    Quaternion rotX;
    m_rotCameraRightAngle += GetPlayerSpeed() * 0.0001f;
    rotX.SetRotation(Vector3::AxisX, m_rotCameraRightAngle);
    m_rotation *= rotX;

    m_modelRender.SetRotation(m_rotation);

    //�v���C���[���i�ޕ��������肷��B
    m_forward = g_camera3D->GetForward();                                       //�J�����̑O����
    m_forward.y = 0.0f;
    m_forward.Normalize();

    m_target = m_rockOn->GetDifference();                                       //���b�N�I�����Ă���I�u�W�F�N�g�̕���

    if (g_pad[0]->IsPress(enButtonLB2))                                         //�{�^���������Ă��鎞
    {
        m_isPress = true;
        if (m_charge < 1.0f)
        {
            m_charge += CHARGE_ADD;
        }
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == false)          //�{�^����������Ċ����b�N�I�����I�t�̎�
    {
        NormalMove();
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == true)           //�{�^����������Ċ����b�N�I�����I���̎�
    {
        RockOnMove();
    }

    if (m_isRockOnFire == true)                                                 //���b�N�I�����Ă鎞
    {
        m_rigidBody.AddForce                                                    //���̂ɗ͂�������
        (
            { m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z },                    //��
            g_vec3Zero                                                          //�͂������鍄�̂̑��Έʒu
        );
    }

    if (m_isRockOnFire == false)
    {
        m_moveSpeed.y = PLAYER_GRAVITY;
        m_rigidBody.AddForce                                                    //���̂ɗ͂�������
        (
            m_moveSpeed,                                                        //��
            g_vec3Zero                                                          //�͂������鍄�̂̑��Έʒu
        );
    }

    //�X�s�[�h�̏����ݒ�B
    if (m_isRockOnFire == false && m_rigidBody.GetLinearVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    //�X�s�[�h�����X�Ɍ���������B
    if (m_rigidBody.GetLinearXZVelocity().Length() >= 0)
    {
        m_rigidBody.SetLinearVelocity(m_rigidBody.GetLinearVelocity() * pow(PLAYER_SPEED_DECREASE, 2));
    }

    //����������Start�{�^���������ꂽ��
    if (m_position.y <= -100 || g_pad[0]->IsTrigger(enButtonStart))
    {
        //�X�e�[�g���ڍs
        m_state = 1;
    }

    if (m_state == 1)
    {
        //���S
        Death();
    }

    //Serect�{�^���������ꂽ��
    if (g_pad[0]->IsTrigger(enButtonSelect))
    {
        //m_game->SetGameState(2);
    }

    m_moveSpeed = { Vector3::Zero };                                            //�X�s�[�h�̏�����
}

void Player::NormalMove()
{
    m_isPressState = true;
    m_isRockOnFire == false;                                                    //���b�N�I���A�^�b�N�𖳌���
    m_isPress = false;                                                          //�{�^����������Ă��Ȃ�

    Vector3 effectpos = { m_position.x,m_position.y + 10.0f,m_position.z };
    Quaternion rot;
    rot.SetRotationYFromDirectionXZ(g_camera3D->GetForward());

    m_effectRotation.SetRotationYFromDirectionXZ(m_cameraRight);
    m_fireImpactEF = NewGO<EffectEmitter>(10);
    m_fireImpactEF->Init(10);
    m_fireImpactEF->SetScale(Vector3::One * 50.0f);
    m_fireImpactEF->SetPosition(effectpos);
    m_fireImpactEF->SetRotation(rot);
    m_fireImpactEF->Play();

    //�T�E���h
    m_shotSE = NewGO<SoundSource>(8);
    m_shotSE->Init(8);
    m_shotSE->SetVolume(0.1f);
    m_shotSE->Play(false);

    //�o�C�u���[�V����
    g_pad[0]->SetVibration(0.2f, 0.05f);

    m_moveSpeed = (m_forward * PLAYER_SPEED_DEFAULT) * m_charge;                //�O��
    m_charge = CHARGE_DEFAULT;                                                  //�`���[�W�����Z�b�g
}

void Player::RockOnMove()
{
    if (m_isPowerCharge == true)
    {
        m_powerCharge = NewGO<PowerCharge>(0, "powerCharge");                   //�G�t�F�N�g���Đ�
    }
    m_isPressState = true;
    m_isPowerCharge = false;
    m_delay += 0.1;                                                             //�f�B���C���Ă���ˏo
    m_rigidBody.SetLinearVelocity(Vector3::Zero);                               //�X�s�[�h��������

    if (m_delay > 2.0f)                                                         //�{�^�����������2.0f���o������
    {
        m_isRockOnFire = true;                                                  //���b�N�I���A�^�b�N��L����
        m_isPress = false;                                                      //�{�^����������Ă��Ȃ�
        m_isPowerCharge = true;

        Vector3 effectpos = { m_position.x,m_position.y + 10.0f,m_position.z };
        Quaternion rot;
        rot.SetRotationYFromDirectionXZ(g_camera3D->GetForward());

        m_effectRotation.SetRotationYFromDirectionXZ(m_cameraRight);
        m_fireImpactEF = NewGO<EffectEmitter>(10);
        m_fireImpactEF->Init(10);
        m_fireImpactEF->SetScale(Vector3::One * EFFECT_FIRE_IMPACT_SIZE);
        m_fireImpactEF->SetPosition(effectpos);
        m_fireImpactEF->SetRotation(rot);
        m_fireImpactEF->Play();

        //�T�E���h
        m_shotSE = NewGO<SoundSource>(8);
        m_shotSE->Init(8);
        m_shotSE->SetVolume(0.1f);
        m_shotSE->Play(false);

        g_pad[0]->SetVibration(0.2f, 0.05f);

        m_moveSpeed = (m_target * PLAYER_SPEED_DEFAULT) * (m_charge * 2.0f);    //�O�� (�ʏ�̓�{�̑����Ŏˏo)
        m_charge = CHARGE_DEFAULT;                                              //�`���[�W�����Z�b�g
        m_delay = 0.0f;                                                         //�f�B���C�����Z�b�g
    }
}