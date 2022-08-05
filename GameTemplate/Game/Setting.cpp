#include "stdafx.h"
#include "Setting.h"

#include "First.h"
#include "Title.h"

namespace
{
	float ZOOM = 1.3f;
}

Setting::Setting()
{

}

Setting::~Setting()
{

}

bool Setting::Start()
{
	m_first = FindGO<First>("first");

	//サウンド
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Jump.wav");
	
	//画像
	m_apply.Init("Assets/sprite/Setting/Apply.dds", 800.0f, 800.0f);
	m_apply.SetPosition({ 200.0f,-300.0f,0.0f });
	m_apply.Update();
	m_applyChoice.Init("Assets/sprite/Setting/ApplyChoice.dds", 800.0f, 800.0f);
	m_applyChoice.SetPosition({ 200.0f,-300.0f,0.0f });
	m_applyChoice.Update();
	m_backGround.Init("Assets/sprite/Setting/BackGround.dds", 1600.0f, 900.0f);
	m_backGround.SetPosition({ 0.0f,0.0f,0.0f });
	m_backGround.Update();
	m_cancel.Init("Assets/sprite/Setting/Cancel.dds", 800.0f, 800.0f);
	m_cancel.SetPosition({ -200.0f,-300.0f,0.0f });
	m_cancel.Update();
	m_cancelChoice.Init("Assets/sprite/Setting/CancelChoice.dds", 800.0f, 800.0f);
	m_cancelChoice.SetPosition({ -200.0f,-300.0f,0.0f });
	m_cancelChoice.Update();
	m_controll.Init("Assets/sprite/Setting/Controll.dds", 800.0f, 800.0f);
	m_controll.SetPosition({ -250.0f,300.0f,0.0f });
	m_controll.Update();
	m_controllChoice.Init("Assets/sprite/Setting/ControllChoice.dds", 800.0f, 800.0f);
	m_controllChoice.SetPosition({ -250.0f,300.0f,0.0f });
	m_controllChoice.Update();
	m_sound.Init("Assets/sprite/Setting/Sound.dds", 800.0f, 800.0f);
	m_sound.SetPosition({ 250.0f,300.0f,0.0f });
	m_sound.Update();
	m_soundChoice.Init("Assets/sprite/Setting/SoundChoice.dds", 800.0f, 800.0f);
	m_soundChoice.SetPosition({ 250.0f,300.0f,0.0f });
	m_soundChoice.Update();
	m_stickSensitivity.Init("Assets/sprite/Setting/StickSensitivity.dds", 800.0f, 800.0f);
	m_stickSensitivity.SetPosition({ -400.0f,100.0f,0.0f });
	m_stickSensitivity.Update();
	m_stickSensitivityChoice.Init("Assets/sprite/Setting/StickSensitivityChoice.dds", 800.0f, 800.0f);
	m_stickSensitivityChoice.SetPosition({ -400.0f,100.0f,0.0f });
	m_stickSensitivityChoice.Update();
	m_stickSensitivityBar.Init("Assets/sprite/Setting/StickSensitivityBar.dds", 300.0f, 300.0f);
	m_stickSensitivityBar.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBar.Update();
	m_stickSensitivityBarChoice.Init("Assets/sprite/Setting/StickSensitivityBarChoice.dds", 300.0f, 300.0f);
	m_stickSensitivityBarChoice.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBarChoice.Update();
	m_stickSensitivityBarInside.Init("Assets/sprite/Setting/StickSensitivityBarInside.dds", 300.0f, 300.0f);
	m_stickSensitivityBarInside.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBarInside.Update();
	m_stickSensitivityBarInsideChoice.Init("Assets/sprite/Setting/StickSensitivityBarInsideChoice.dds", 300.0f, 300.0f);
	m_stickSensitivityBarInsideChoice.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBarInsideChoice.Update();
	m_vibration.Init("Assets/sprite/Setting/Vibration.dds", 800.0f, 800.0f);
	m_vibration.SetPosition({ -400.0f,0.0f,0.0f });
	m_vibration.Update();
	m_vibrationChoice.Init("Assets/sprite/Setting/VibrationChoice.dds", 800.0f, 800.0f);
	m_vibrationChoice.SetPosition({ -400.0f,0.0f,0.0f });
	m_vibrationChoice.Update();

	return true;
}

void Setting::Update()
{
	Choice();
	Sprite();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_first->SetIsCreate(true);
		DeleteGO(this);
	}
	//デバッグ用
	wchar_t x[256];
	swprintf_s(x, 256, L"Sensi=%i", m_stickSensitivityNum);
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ 500.0f, -300.0f, 0.0f });
}

void Setting::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_backGround.Draw(rc);
	
	//コントロール
	if (m_scale >= 0.8f)
	{
		if (m_shelf == 0)
		{
			m_controllChoice.Draw(rc);
		}
		else
		{
			m_controll.Draw(rc);
		}
		if (m_shelf == 0 && m_choiceState == 0)
		{
			m_stickSensitivityChoice.Draw(rc);
			m_stickSensitivityBarChoice.Draw(rc);
			m_stickSensitivityBarInsideChoice.Draw(rc);
		}
		else if (m_shelf != 1)
		{
			m_stickSensitivity.Draw(rc);
			m_stickSensitivityBar.Draw(rc);
			m_stickSensitivityBarInside.Draw(rc);
		}
		if (m_shelf == 0 && m_choiceState == 1)
		{
			m_vibrationChoice.Draw(rc);
		}
		else if (m_shelf != 1)
		{
			m_vibration.Draw(rc);
		}
		if (m_shelf == 0 && m_choiceState == 2)
		{
			m_cancelChoice.Draw(rc);
		}
		else
		{
			m_cancel.Draw(rc);
		}
		if (m_shelf == 0 && m_choiceState == 3)
		{
			m_applyChoice.Draw(rc);
		}
		else
		{
			m_apply.Draw(rc);
		}

		//サウンド
		if (m_shelf == 1)
		{
			m_soundChoice.Draw(rc);
		}
		else
		{
			m_sound.Draw(rc);
		}
	}
}

void Setting::Choice()
{
	/// <summary>
	/// 設定項目の切替
	/// </summary>
	if (m_shelf == 0 && g_pad[0]->IsTrigger(enButtonRB1))
	{
		m_shelf = 1;
		m_choiceState = 0;

		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(0.3f);
		m_choiceSE->Play(false);
	}
	else if (m_shelf == 1 && g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_shelf = 0;
		m_choiceState = 0;

		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(0.3f);
		m_choiceSE->Play(false);
	}

	/// <summary>
	/// 選択項目の切替
	/// </summary>
	if (m_choiceState >= 0 && m_choiceState < 2 && g_pad[0]->IsTrigger(enButtonDown))
	{
		m_choiceState += 1;

		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(0.3f);
		m_choiceSE->Play(false);
	}

	if (m_choiceState <= 2 && m_choiceState > 0 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_choiceState -= 1;

		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->SetVolume(0.3f);
		m_choiceSE->Play(false);
	}

	/// <summary>
	/// 感度
	/// </summary>
	if (m_shelf == 0)															//コントロールが選択されている時
	{
		if (m_choiceState == 0)													//スティック感度項目が選択されている時
		{
			if (m_stickSensitivityNum >= 1 && m_stickSensitivityNum < 10)
			{
				m_stickSensitivityUp = true;									//感度を上げられる様にする
			}
			else
			{
				m_stickSensitivityUp = false;									//感度を上げられない様にする
			}

			if (m_stickSensitivityNum >= 2 && m_stickSensitivityNum < 11)
			{
				m_stickSensitivityDown = true;									//感度を下げられる様にする
			}
			else
			{
				m_stickSensitivityDown = false;									//感度を下げられない様にする
			}

			if (m_stickSensitivityUp == true && g_pad[0]->IsTrigger(enButtonRight))
			{
				m_stickSensitivityNum += 1.0f;									//感度を上げる
			}

			else if (m_stickSensitivityDown == true && g_pad[0]->IsTrigger(enButtonLeft))
			{
				m_stickSensitivityNum -= 1.0f;									//感度を下げる
			}
		}
		if (m_choiceState == 1)													//バイブレーションが選択されている時
		{

		}
	}

	/// <summary>
	/// キャンセルと適用
	/// </summary>
	if (m_choiceState == 2)														//キャンセルが選択されている時
	{
		if (g_pad[0]->IsTrigger(enButtonRight))									//右ボタンを押すと
		{
			m_choiceState += 1;													//適用に切替

			m_choiceSE = NewGO<SoundSource>(1);
			m_choiceSE->Init(1);
			m_choiceSE->SetVolume(0.3f);
			m_choiceSE->Play(false);
		}
		else if ( g_pad[0]->IsTrigger(enButtonB))								//Bボタンを押すと
		{
			m_first->SetIsCreate(true);											//タイトルに戻る
			DeleteGO(this);
		}
	}
	
	if (m_choiceState == 3)														//適用が選択されている時
	{
		if (g_pad[0]->IsTrigger(enButtonLeft))									//左ボタンを押すと
		{
			m_choiceState -= 1;													//キャンセルに切替

			m_choiceSE = NewGO<SoundSource>(1);
			m_choiceSE->Init(1);
			m_choiceSE->SetVolume(0.3f);
			m_choiceSE->Play(false);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))								//上ボタンを押すと
		{
			m_choiceState -= 2;													//キャンセルを飛ばして選択項目に移る

			m_choiceSE = NewGO<SoundSource>(1);
			m_choiceSE->Init(1);
			m_choiceSE->SetVolume(0.3f);
			m_choiceSE->Play(false);
		}
		else if (g_pad[0]->IsTrigger(enButtonB))								//Bボタンを押すと
		{

		}
	}
}

void Setting::Sprite()
{
	if (m_scale <= 1.0f)
	{
		m_scale += 0.1f;
	}

	m_backGround.SetScale({ 1.0f,m_scale,1.0f });
	m_backGround.Update();

	/// <summary>
	/// コントロール
	/// </summary>
	if (m_shelf == 0)
	{
		m_controllChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_controllChoice.Update();
	}
	else
	{
		m_controllChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_controllChoice.Update();
	}
	//スティック感度
	if (m_shelf == 0 && m_choiceState == 0)
	{
		m_stickSensitivityChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_stickSensitivityChoice.Update();
		m_stickSensitivityBarInside.SetIsDisplayRestrictionRightSide(true);
		m_stickSensitivityBarInside.SetLimitedX(m_stickSensitivityNum / 10);
		m_stickSensitivityBarInsideChoice.SetIsDisplayRestrictionRightSide(true);
		m_stickSensitivityBarInsideChoice.SetLimitedX(m_stickSensitivityNum / 10);
	}
	else
	{
		m_stickSensitivityChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_stickSensitivityChoice.Update();
	}
	//バイブレーション
	if (m_shelf == 0 && m_choiceState == 1)
	{
		m_vibrationChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_vibrationChoice.Update();
	}
	else
	{
		m_vibrationChoice.SetScale({ 1.0f,1.0f,1.0f });
		m_vibrationChoice.Update();
	}
	//キャンセル
	if (m_shelf == 0 && m_choiceState == 2)
	{
		m_cancelChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_cancelChoice.Update();
	}
	else
	{
		m_cancelChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_cancelChoice.Update();
	}
	//適用
	if (m_shelf == 0 && m_choiceState == 3)
	{
		m_applyChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_applyChoice.Update();
	}
	else
	{
		m_applyChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_applyChoice.Update();
	}

	/// <summary>
	/// サウンド
	/// </summary>
	if (m_shelf == 1)
	{
		m_soundChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_soundChoice.Update();
	}
	else
	{
		m_soundChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_soundChoice.Update();
	}
}