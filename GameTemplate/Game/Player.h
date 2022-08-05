#pragma once

class BreakBox;
class Bumper;
class Game;
class GameCamera;
class PowerCharge;
class RockOn;
class FireImpact;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;
    void UpdateOnStop() override;
    /// <summary>
    /// ステートを設定
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    int SetState(const int& state)
    {
        m_state = state;
        return m_state;
    }

    /// <summary>
    /// 座標を設定
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(const Vector3& position)
    {
        m_position = position;
    }

    /// <summary>
    /// 大きさを設定。
    /// </summary>
    /// <param name="scale">大きさ。</param>
    void SetScale(const float& scale)
    {
        m_scale = scale;
    }

    /// <summary>
    /// 回転を設定。
    /// </summary>
    /// <param name="rotation">回転。</param>
    void SetRotation(const Quaternion& rotation)
    {
        m_rotation = rotation;
    }

    /// <summary>
    /// プレイヤーの移動速度を設定。
    /// </summary>
    /// <param name="moveSpeed"></param>
    void SetMoveSpeed(const Vector3& moveSpeed)
    {
        m_moveSpeed = moveSpeed;
    }

    /// <summary>
    /// ロックオン時に発射されたか否か。
    /// </summary>
    /// <param name="judge"></param>
    void SetIsRockOnFire(const bool& judge)
    {
        m_isRockOnFire = judge;
    }

    /// <summary>
    /// リスポーン地点を設定。
    /// </summary>
    /// <param name="reSpawnPosition"></param>
    void SetReSpawnPosition(Vector3& reSpawnPosition)
    {
        m_reSpawnPosition = reSpawnPosition;
    }

    /// <summary>
    /// ステートを取得
    /// </summary>
    /// <returns></returns>
    int GetState() const
    {
        return m_state;
    }

    /// <summary>
    /// ボタンの入力情報を取得
    /// </summary>
    /// <returns></returns>
    bool GetIsPressState() const
    {
        return m_isPressState;
    }

    /// <summary>
    /// ボタンの入力情報を設定
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    bool SetIsPressState(const bool& state)
    {
        m_isPressState = state;
        return 0;
    }

    /// <summary>
    /// 座標を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() const
    {
        return m_position;
    }

    /// <summary>
    /// チャージ量を取得。
    /// </summary>
    /// <returns></returns>
    float GetCharge() const
    {
        return m_charge;
    }

    /// <summary>
    /// プレイヤーのスピードを取得
    /// </summary>
    /// <returns></returns>
    float GetPlayerSpeed() const
    {
        return m_rigidBody.GetLinearVelocity().Length();
    }
    /// <summary>
    /// 1フレームでの座標の変位量を取得。
    /// </summary>
    /// <returns></returns>
    const Vector3& GetPositionDeltaValue() const
    {
        return m_positionDeltaValue;
    }
    RigidBody           m_rigidBody;                //剛体

private:

    /// <summary>
    /// デスの判定
    /// </summary>
    void Death();

    /// <summary>
    /// リスポーン
    /// </summary>
    void ReSpawn();

    /// <summary>
    /// 動作を管理
    /// </summary>
    void Move();

    /// <summary>
    /// ロックオンしてない時の動作を管理
    /// </summary>
    void NormalMove();

    /// <summary>
    /// ロックオンしている時の動作を管理
    /// </summary>
    void RockOnMove();
    
    EffectEmitter*      m_deathEF;
    EffectEmitter*      m_reSpawnEF;
    EffectEmitter*      m_fireImpactEF;
    SoundSource*        m_shotSE;
    SoundSource*        m_deathSE;
    SoundSource*        m_reSpawnSE;
   
    FontRender          m_fontRenderX;                  //フォントレンダー
    FontRender          m_fontRenderY;                  //フォントレンダー
    FontRender          m_fontRenderZ;                  //フォントレンダー
    FontRender          m_fpsFont;
    ModelRender         m_modelRender;                  //モデルレンダー
    SphereCollider      m_sphereCollider;               //円型のコライダー
    Vector3             m_positionDeltaValue;           //1フレームでの座標の変位量
    Vector3             m_position;                     //ポジション
    Vector3             m_reSpawnPosition;              //リスポーンポイント
    Vector3             m_cameraForward;                //カメラの前方向
    Vector3             m_cameraRight;                  //カメラの左右方向
    Vector3             m_moveSpeed;                    //プレイヤーの移動速度
    Vector3             m_rockOnTarget;
    Vector3             m_forward;
    Vector3             m_target;

    Quaternion          m_rotation;                     //回転
    Quaternion          m_effectRotation;               //エフェクトの回転

    bool                m_isEffectStart = true;         //エフェクトを一回だけ再生させる
    bool                m_isPress = false;              //ボタンが押されているか否かの判定
    bool                m_isRockOnFire = false;         //ロックオン時に発射されたか否かの判定
    bool                m_isPowerCharge = true;         //パワーチャージエフェクト
    bool                m_stopNormal = false;
    bool                m_stopRockOn = false;
    bool                m_isPressState = false;
    int                 m_state;                        //ステート
    float               m_scale = 0.0f;                 //サイズ
    float               m_charge = 0.0f;                //チャージ
    float               m_delay = 0.0f;                 //ディレイ
    float               m_deathTime = 0.0f;
    float               m_stopTimer = 0.0f;
    float               m_rotCameraRightAngle = 0.0f;   //カメラの右方向を軸とした回転角度。
   
    BreakBox*           m_breakBox;
    Bumper*             m_bumper;
    Game*               m_game;
    GameCamera*         m_gameCamera;
    PowerCharge*        m_powerCharge;
    RockOn*             m_rockOn;
};