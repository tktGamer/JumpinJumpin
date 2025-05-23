#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"pch.h"

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class Sound
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundSource;
	DirectX::SoundEffect* m_pSoundEffect;

	float m_volume;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Sound(DirectX::SoundEffect* pSoundEffect);

	// �f�X�g���N�^
	~Sound();


// ����
public:
	// �Đ�
	void Play(bool isLoop);
	//��~
	void Stop();
// �擾/�ݒ�
public:
	// ���ʐݒ�
	void SetVolume(float volume=1.0f);
// ��������
private:
	// �C���X�^���X�̍쐬
	void CreateInstance();
	// ���ʕύX
	void ChangeVolume();
};

