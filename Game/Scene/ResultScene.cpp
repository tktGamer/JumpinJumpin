/**
 * @file   ResultScene.cpp
 *
 * @brief  ���U���g�V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "ResultScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
ResultScene::ResultScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_spriteBatch{}
	, m_resultTexture{}
	, m_pressTexture{}
	, m_clearSound{}
	, m_gameoverSound{}
	, m_isClear{}
{
	m_clearSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("clear.wav"));
	m_gameoverSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("gameover.wav"));
}



/**
 * @brief �f�X�g���N�^
 */
ResultScene::~ResultScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void ResultScene::Initialize()
{
	ReadSharedData("result",&m_isClear);
	m_spriteBatch = m_pResourceManager->GetSpriteBatch();
	if (m_isClear)
	{
		m_backTexture = m_pResourceManager->RequestDDSTexture("clearback.dds");
		m_resultTexture = m_pResourceManager->RequestDDSTexture("clear.dds");
		m_clearSound->Play(false);

	}
	else
	{
		m_backTexture = m_pResourceManager->RequestDDSTexture("gameoverback.dds");
		m_resultTexture = m_pResourceManager->RequestDDSTexture("gameover.dds");
		m_gameoverSound->Play(false);
	}
	m_pressTexture = m_pResourceManager->RequestDDSTexture("guide.dds");

}



/**
 * @brief �X�V����
 *
 * @param[in] inputDevice ���̓f�o�C�X
 *
 * @return �Ȃ�
 */
void ResultScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	// �V�[���̐؂�ւ�
	if (traker->pressed.Space) 
	{
		m_clearSound->Stop();
		m_gameoverSound->Stop();
		ChangeScene("Title");
	}
	else if (traker->pressed.Enter)
	{
		m_clearSound->Stop();
		m_gameoverSound->Stop();
		ChangeScene("Game");
	}

}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void ResultScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_backTexture, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->Draw(m_resultTexture, DirectX::SimpleMath::Vector2(300, 50));
	m_spriteBatch->Draw(m_pressTexture, DirectX::SimpleMath::Vector2(300, 400));
	m_spriteBatch->End();
	//DrawFormatString(10, 10, Colors::WHITE, "�^�C�g���V�[��");
	//DrawFormatString(500, 200, Colors::WHITE, "JumpinJumpin");
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void ResultScene::Finalize()
{
	
}
