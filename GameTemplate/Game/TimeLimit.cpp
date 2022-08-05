#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"
#include "GameOver.h"

namespace
{
    const Vector3 SET_1_DIGIT_POSITION = { 133.0f, 405.0f, 0.0f };          //�c�莞�Ԃ�1���̎��̃t�H���g�̈ʒu
    const Vector3 SET_2_DIGIT_POSITION = { 120.0f, 405.0f, 0.0f };          //�c�莞�Ԃ�2���̎��̃t�H���g�̈ʒu
    const Vector3 SET_COLOR = { 0.0f,230.0f,255.0f };                       //�t�H���g�̃J���[
    const float SET_TIMELIMIT = 3000.0f;                                      //�^�C�����~�b�g
    const float SET_DEFAULT_SCALE = 1.5f;                                   //�t�H���g�̃T�C�Y
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
    //�c�莞�Ԃ�20�b��؂������ʂɐԂ݂��o��
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
    //����s�\�̎�
    if (m_game->GetGameState() == 1)
    {
        //�������^�[��
        return;
    }

    //�c�莞�Ԃ����炷
    m_limitTimer -= g_gameTime->GetFrameDeltaTime();

    //���Ԑ؂�ɂȂ�����
    if (m_limitTimer <= 0)
    {
        //����s�\�ɂ���
        m_game->SetGameState(1);
        //�Q�[���I�[�o�[���o������
        m_gameOver = NewGO<GameOver>(0, "gameOver");
        DeleteGO(this);
    }

    //�c�莞�Ԃ�2���̎�
    if (m_limitTimer < 10)
    {
        //�|�W�V������2���p��
        m_fontRender.SetPosition(SET_1_DIGIT_POSITION);
        //�v���C���[���A�C�e�����������
        if (m_isSetScale == true)
        {
            //�t�H���g���㉺�ɓ�����
            if (m_fontYPosition > 0.0f)
            {
                m_fontYPosition -= 5.0f;
            }
            m_fontRender.SetPosition({ SET_1_DIGIT_POSITION.x, SET_1_DIGIT_POSITION.y + m_fontYPosition,SET_1_DIGIT_POSITION.z });
        }
    }
    //�c�莞�Ԃ�1���̎�
    else
    {   //�|�W�V������1���p��
        m_fontRender.SetPosition(SET_2_DIGIT_POSITION);
        //�v���C���[���A�C�e�����������
        if (m_isSetScale == true)
        {
            //�t�H���g���㉺�ɓ�����
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