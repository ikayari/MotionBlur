#pragma once

class Game;
class Goal;

/// <summary>
/// �`���[�W�Q�[�W
/// </summary>
class Length : public IGameObject
{
public:

	Length();
	~Length();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// �o�[�̕\�����Ǘ�
	/// </summary>
	void Cut();

	/// <summary>
	/// �t�F�[�h����
	/// </summary>
	void Fade();

	/// <summary>
	/// �X�s�[�h�\�L�̊Ǘ�
	/// </summary>
	void LengthFont();

	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
	};
	EnState			m_fadeState;

	//�摜
	SpriteRender	m_length2D;
	SpriteRender	m_lengthInside2D;

	//�t�H���g
	FontRender		m_fontRender;

	bool			m_isPress = false;

	float			m_timer = 0.0f;
	float			m_charge = 0.0f;
	float			m_length = 0.0f;
	float			m_InitialLength = 0.0f;
	float			m_currentAlpha = 0.0f;		//a�l�B

	Game*			m_game;
	Goal*			m_goal;
};