/**
 * @file   LogoScene.cpp
 *
 * @brief  ���S�V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "LogoScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
LogoScene::LogoScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }

{

}



/**
 * @brief �f�X�g���N�^
 */
LogoScene::~LogoScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LogoScene::Initialize()
{
	//m_texture = m_pResourceManager->RequestTexture("Logo.png");
	//// ���S�p�X�v���C�g�̏�����
	//m_sprite.Initialize(m_texture, { 0,0,60,80 }, 2.0f);

	//// ���S�p�A�j���[�^�[�̏�����
	//m_spriteAnimator.Initialize(&m_sprite, LOGO_CLIP);
	//m_spritePostion = { 640.0f,360.0f };

	//m_spriteAnimator.Play();
	//m_change = false;

}



/**
 * @brief �X�V����
 *
 * @param[in] inputDevice ���̓f�o�C�X
 *
 * @return �Ȃ�
 */
void LogoScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{
	//�A�j���[�V�������I�������J�ڋ���
	//if (m_spriteAnimator.IsFinished() || joypad.IsButtonPressed(PAD_INPUT_10))
	//{
	//	m_change = true;
	//}
	// ���S�p�A�j���[�^�[�̍X�V
	//m_spriteAnimator.Update();
	//// �V�[���̐؂�ւ�
	//if (m_change)
	//{
	//	ChangeScene("Title");
	//}

}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LogoScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{

	//���S�`��
	//m_sprite.Draw(m_spritePostion);

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LogoScene::Finalize()
{
	
}
