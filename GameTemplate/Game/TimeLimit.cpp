#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"
#include "GameOver.h"

namespace
{
    const Vector3 SET_1_DIGIT_POSITION = { 133.0f, 405.0f, 0.0f };          //残り時間が1桁の時のフォントの位置
    const Vector3 SET_2_DIGIT_POSITION = { 120.0f, 405.0f, 0.0f };          //残り時間が2桁の時のフォントの位置
    const Vector3 SET_COLOR = { 0.0f,230.0f,255.0f };                       //フォントのカラー
    const float SET_TIMELIMIT = 3000.0f;                                      //タイムリミット
    const float SET_DEFAULT_SCALE = 1.5f;                                   //フォントのサイズ
}

TimeLimit::TimeLimit()
{

}

TimeLimit::~TimeLimit()
{

}

bool TimeLimit::Start()
{
    m_game = FindGO<Game>("game");

    m_limitTimer = SET_TIMELIMIT;

    m_fontRender.SetPosition(SET_1_DIGIT_POSITION);
    m_fontRender.SetScale(SET_DEFAULT_SCALE);
    m_fontRender.SetColor(SET_COLOR);
    m_fontRender.SetPivot(1.0f, 1.0f);

    return true;
}

void TimeLimit::Update()
{
    Time();

    if (m_isRed)
    {
        g_renderingEngine.SetRed(g_renderingEngine.GetRed() + 0.05f);
    }
    else
    {
        g_renderingEngine.SetRed(g_renderingEngine.GetRed() - 0.05f);
    }
    //残り時間が20秒を切ったら画面に赤みを出す
    if (m_limitTimer <= 20.0f)
    {
        if (g_renderingEngine.GetRed() <= 1.0f)
        {
            m_isRed = true;
        }
        if (g_renderingEngine.GetRed() >= 2.5f)
        {
            m_isRed = false;
        }
    }
    else
    {
        g_renderingEngine.SetRed(0.7f);
    }
}

void TimeLimit::Render(RenderContext& rc)
{
    if (m_game->GetGameState() == 0)
    {
        m_fadeState = enState_FadeOut;
        m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,m_currentAlpha });
        m_fontRender.Draw(rc);
    }
}

void TimeLimit::Fade()
{
    switch (m_fadeState) {
    case enState_FadeIn:
        m_currentAlpha -= g_gameTime->GetFrameDeltaTime();
        if (m_currentAlpha <= 0.0f) {
            m_currentAlpha = 0.0f;
            m_fadeState = enState_Idle;
        }
        break;
    case enState_FadeOut:
        m_currentAlpha += g_gameTime->GetFrameDeltaTime();
        if (m_currentAlpha >= 1.0f) {
            m_currentAlpha = 1.0f;
            m_fadeState = enState_Idle;
        }
        break;
    case enState_Idle:
        break;
    }
}

void TimeLimit::Time()
{
    //操作不能の時
    if (m_game->GetGameState() == 1)
    {
        //早期リターン
        return;
    }

    //残り時間を減らす
    m_limitTimer -= g_gameTime->GetFrameDeltaTime();

    //時間切れになったら
    if (m_limitTimer <= 0)
    {
        //操作不能にする
        m_game->SetGameState(1);
        //ゲームオーバー演出をする
        m_gameOver = NewGO<GameOver>(0, "gameOver");
        DeleteGO(this);
    }

    //残り時間が2桁の時
    if (m_limitTimer < 10)
    {
        //ポジションを2桁用に
        m_fontRender.SetPosition(SET_1_DIGIT_POSITION);
        //プレイヤーがアイテムを取ったら
        if (m_isSetScale == true)
        {
            //フォントを上下に動かす
            if (m_fontYPosition > 0.0f)
            {
                m_fontYPosition -= 5.0f;
            }
            m_fontRender.SetPosition({ SET_1_DIGIT_POSITION.x, SET_1_DIGIT_POSITION.y + m_fontYPosition,SET_1_DIGIT_POSITION.z });
        }
    }
    //残り時間が1桁の時
    else
    {   //ポジションを1桁用に
        m_fontRender.SetPosition(SET_2_DIGIT_POSITION);
        //プレイヤーがアイテムを取ったら
        if (m_isSetScale == true)
        {
            //フォントを上下に動かす
            if (m_fontYPosition > 0.0f)
            {
                m_fontYPosition -= 5.0f;
            }
            m_fontRender.SetPosition({ SET_2_DIGIT_POSITION.x, SET_2_DIGIT_POSITION.y + m_fontYPosition,SET_2_DIGIT_POSITION.z });
        }
    }

    wchar_t x[256];
    swprintf_s(x, 256, L"%d", int(m_limitTimer));
    m_fontRender.SetText(x);
}