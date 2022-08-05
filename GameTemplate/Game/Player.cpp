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
    //プレイヤー
    const Vector3 PLAYER_FIRST_POSITION = { 0.0f,250.0f,0.0f };             //スポーン座標
    const float PLAYER_MODEL_SCALE = 1.0f;                                  //サイズ
    const float PLAYER_COLLISION_SCALE = 50.0f;                             //当たり判定のサイズ
    const float PLAYER_GRAVITY = -200000.0f;                                //重力
    const float PLAYER_ROLL = 1.0f;                                         //転がりやすさ
    const float PLAYER_FRICTION = 1.0f;                                     //摩擦力
    const float PLAYER_SPEED_DECREASE = 0.997;                              //スピードの減衰率
    const float PLAYER_SPEED_DEFAULT = 50000000.0f;                         //スピードデフォルト
    const float PLAYER_SPEED_MAX = 10000.0f;                                //スピード上限値

    //チャージ
    const float CHARGE_DEFAULT = 0.0f;                                      //sチャージリセット値
    const float CHARGE_ADD = 0.05f;                                         //1f毎にチャージされる値

    //エフェクト
    const float EFFECT_RESPWAN_SIZE = 3.0f;                                 //リスポーンエフェクトのサイズ
    const float EFFECT_FIRE_IMPACT_SIZE = 50.0f;                            //発射時のエフェクトのサイズ
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
    //球形のモデルを読み込む。
    m_modelRender.SetCasterShadow(true);
    m_modelRender.Init("Assets/modelData/Stage_0/Player.tkm");
    m_modelRender.SetPosition(m_position);

    //エフェクト
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

    //サウンド
    g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Shot.wav");
    g_soundEngine->ResistWaveFileBank(15, "Assets/sound/ReSpawn.wav");
    g_soundEngine->ResistWaveFileBank(22, "Assets/sound/Death.wav");

    //コライダーを初期化。
    m_sphereCollider.Create(PLAYER_COLLISION_SCALE);

    //剛体を初期化。
    RigidBodyInitData rbInitData;
    //質量(重さ)を設定する。
    rbInitData.mass = 30.0f;
    //コライダーを設定する。
    rbInitData.collider = &m_sphereCollider;
    //座標を設定する。
    rbInitData.pos = m_position;
    //回転のしやすさを設定する。0～1
    rbInitData.localInteria.Set(
        0.5f,
        0.5f,
        0.5f
    );
    //反発力を設定する。
    //数値を大きくすると、跳ね返りが大きくなる。
    //PhysicsStaticObjectにも反発力を設定する必要がある(Game.cpp参照)。
    rbInitData.restitution = 1.0f;
    //剛体を初期化。
    m_rigidBody.Init(rbInitData);
    //摩擦力を設定する。0～10まで。
    m_rigidBody.SetFriction(PLAYER_FRICTION);
    //線形移動する要素を設定する。
    //0を指定した軸は移動しない。
    //例えばyを0に指定すると、y座標は移動しなくなる。
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

    return true;
}

void Player::Update()
{
    Move();
    //モデルの更新処理。
    m_modelRender.Update();

    //デバッグ用
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
    //モデルの描画。
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
        //エフェクト
        m_deathEF = NewGO<EffectEmitter>(22);
        m_deathEF->Init(22);
        m_deathEF->SetScale(Vector3::One * 20.0f);
        m_deathEF->Play();

        //サウンド
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

    //エフェクト
    m_reSpawnEF = NewGO<EffectEmitter>(2);
    m_reSpawnEF->Init(2);
    m_reSpawnEF->SetScale(Vector3::One * EFFECT_RESPWAN_SIZE);
    m_reSpawnEF->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z });
    m_reSpawnEF->Play();

    //サウンド
    m_reSpawnSE = NewGO<SoundSource>(15);
    m_reSpawnSE->Init(15);
    m_reSpawnSE->SetVolume(0.175f);
    m_reSpawnSE->Play(false);

    //バイブレーション
    g_pad[0]->SetVibration(0.3f, 0.05f);

    g_camera3D->SetPosition(m_position);
    g_camera3D->SetTarget(m_position);
    m_state = 0;
}

void Player::Move()
{
    //ゲームステートが1(行動不能)だったら
    if (m_game->GetGameState() != 0)
    {
        //早期リターン
        m_rigidBody.SetLinearVelocity(Vector3::Zero);
        return;
    }

    if (m_scale <= 1.0f)
    {
        m_scale += 0.1;
    }
    m_modelRender.SetScale(Vector3::One * m_scale);

    //剛体の座標と回転を取得。
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);

    //剛体の座標と回転をモデルに反映。
    m_modelRender.SetPosition(m_position);
    Matrix cameraRotationMatrix = g_camera3D->GetCameraRotation();
    m_rotation.SetRotation(cameraRotationMatrix);
    Quaternion rotX;
    m_rotCameraRightAngle += GetPlayerSpeed() * 0.0001f;
    rotX.SetRotation(Vector3::AxisX, m_rotCameraRightAngle);
    m_rotation *= rotX;

    m_modelRender.SetRotation(m_rotation);

    //プレイヤーが進む方向を決定する。
    m_forward = g_camera3D->GetForward();                                       //カメラの前方向
    m_forward.y = 0.0f;
    m_forward.Normalize();

    m_target = m_rockOn->GetDifference();                                       //ロックオンしているオブジェクトの方向

    if (g_pad[0]->IsPress(enButtonLB2))                                         //ボタンを押している時
    {
        m_isPress = true;
        if (m_charge < 1.0f)
        {
            m_charge += CHARGE_ADD;
        }
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == false)          //ボタンが離されて且つロックオンがオフの時
    {
        NormalMove();
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == true)           //ボタンが離されて且つロックオンがオンの時
    {
        RockOnMove();
    }

    if (m_isRockOnFire == true)                                                 //ロックオンしてる時
    {
        m_rigidBody.AddForce                                                    //剛体に力を加える
        (
            { m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z },                    //力
            g_vec3Zero                                                          //力を加える剛体の相対位置
        );
    }

    if (m_isRockOnFire == false)
    {
        m_moveSpeed.y = PLAYER_GRAVITY;
        m_rigidBody.AddForce                                                    //剛体に力を加える
        (
            m_moveSpeed,                                                        //力
            g_vec3Zero                                                          //力を加える剛体の相対位置
        );
    }

    //スピードの上限を設定。
    if (m_isRockOnFire == false && m_rigidBody.GetLinearVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    //スピードを徐々に減衰させる。
    if (m_rigidBody.GetLinearXZVelocity().Length() >= 0)
    {
        m_rigidBody.SetLinearVelocity(m_rigidBody.GetLinearVelocity() * pow(PLAYER_SPEED_DECREASE, 2));
    }

    //落下したかStartボタンが押されたら
    if (m_position.y <= -100 || g_pad[0]->IsTrigger(enButtonStart))
    {
        //ステートを移行
        m_state = 1;
    }

    if (m_state == 1)
    {
        //死亡
        Death();
    }

    //Serectボタンが押されたら
    if (g_pad[0]->IsTrigger(enButtonSelect))
    {
        //m_game->SetGameState(2);
    }

    m_moveSpeed = { Vector3::Zero };                                            //スピードの初期化
}

void Player::NormalMove()
{
    m_isPressState = true;
    m_isRockOnFire == false;                                                    //ロックオンアタックを無効化
    m_isPress = false;                                                          //ボタンが押されていない

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

    //サウンド
    m_shotSE = NewGO<SoundSource>(8);
    m_shotSE->Init(8);
    m_shotSE->SetVolume(0.1f);
    m_shotSE->Play(false);

    //バイブレーション
    g_pad[0]->SetVibration(0.2f, 0.05f);

    m_moveSpeed = (m_forward * PLAYER_SPEED_DEFAULT) * m_charge;                //前後
    m_charge = CHARGE_DEFAULT;                                                  //チャージをリセット
}

void Player::RockOnMove()
{
    if (m_isPowerCharge == true)
    {
        m_powerCharge = NewGO<PowerCharge>(0, "powerCharge");                   //エフェクトを再生
    }
    m_isPressState = true;
    m_isPowerCharge = false;
    m_delay += 0.1;                                                             //ディレイしてから射出
    m_rigidBody.SetLinearVelocity(Vector3::Zero);                               //スピードを初期化

    if (m_delay > 2.0f)                                                         //ボタンが離されて2.0fが経ったら
    {
        m_isRockOnFire = true;                                                  //ロックオンアタックを有効化
        m_isPress = false;                                                      //ボタンが押されていない
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

        //サウンド
        m_shotSE = NewGO<SoundSource>(8);
        m_shotSE->Init(8);
        m_shotSE->SetVolume(0.1f);
        m_shotSE->Play(false);

        g_pad[0]->SetVibration(0.2f, 0.05f);

        m_moveSpeed = (m_target * PLAYER_SPEED_DEFAULT) * (m_charge * 2.0f);    //前後 (通常の二倍の速さで射出)
        m_charge = CHARGE_DEFAULT;                                              //チャージをリセット
        m_delay = 0.0f;                                                         //ディレイをリセット
    }
}