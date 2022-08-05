#include "stdafx.h"
#include "PowerCharge.h"

#include "Player.h"

PowerCharge::PowerCharge()
{

}

PowerCharge::~PowerCharge()
{

}

bool PowerCharge::Start()
{
    m_player = FindGO<Player>("player");

    EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Selfmade/PowerCharge.efk");
    m_powerCharge = NewGO<EffectEmitter>(2);
    m_powerCharge->Init(2);
    m_powerCharge->SetScale(Vector3::One * 20.0f);
    m_powerCharge->SetPosition(m_position);
    m_powerCharge->Play();

    g_soundEngine->ResistWaveFileBank(2, "Assets/sound/PowerCharge.wav");
    m_powerChargeSE = NewGO<SoundSource>(2);
    m_powerChargeSE->Init(2);
    m_powerChargeSE->SetVolume(0.1f);
    m_powerChargeSE->Play(false);
  
    return true;
}

void PowerCharge::Update()
{
    m_position = m_player->GetPosition();
    m_powerCharge->SetPosition(m_position);

    m_aliveTimer += g_gameTime->GetFrameDeltaTime();
    if (m_aliveTimer > 0.3f)
    {
        m_powerCharge->Stop();
        DeleteGO(this);
    }
}