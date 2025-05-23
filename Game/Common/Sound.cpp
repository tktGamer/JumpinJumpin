// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Sound.h"


// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] pSoundEffect
 */
Sound::Sound(DirectX::SoundEffect* pSoundEffect)
	:m_soundSource{}
	, m_pSoundEffect{ pSoundEffect }
	, m_volume{ 1.0f }
{
}
/**
 * @brief �f�X�g���N�^
 */
Sound::~Sound()
{
}

/**
 * @brief �Đ�
 *
 * @param[in] isLoop ���[�v�Đ����邩�ǂ���
 *
 * @return �Ȃ�
 */
void Sound::Play(bool isLoop)
{
	CreateInstance();
	ChangeVolume();
	m_soundSource->Play(isLoop);
}

/**
 * @brief ��~
 * 
 * @param[in] �Ȃ�
 * 
 * @return �Ȃ�
 */
void Sound::Stop()
{
	CreateInstance();
	m_soundSource->Stop();
}

/**
 * @brief ���ʐݒ�
 *
 * @param[in] volume ���� 0.0f�`1.0f
 *
 * @return �Ȃ�
 */
void Sound::SetVolume(float volume)
{
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	else if (volume > 1.0f)
	{
		volume = 1.0f;
	}
	m_volume = volume;
}

/**
 * @brief �C���X�^���X�̍쐬
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Sound::CreateInstance()
{
	m_soundSource = m_pSoundEffect->CreateInstance();
}

/**
 * @brief ���ʕύX
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Sound::ChangeVolume()
{
	m_soundSource->SetVolume(m_volume);
}
