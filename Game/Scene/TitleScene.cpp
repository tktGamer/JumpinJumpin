/**
 * @file   TitleScene.cpp
 *
 * @brief  �^�C�g���V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "TitleScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
TitleScene::TitleScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_spriteBatch{}
	, m_titleTexture{}
	, m_backTexture{}

	, m_rotationY{ 0.0f }
	, m_model{}
{
	m_camera = std::make_unique<Camera>();
	m_decideSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("decide.wav"));
	m_bgm = std::make_unique<Sound>(m_pResourceManager->RequestSound("titlebgm.wav"));
}



/**
 * @brief �f�X�g���N�^
 */
TitleScene::~TitleScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Initialize()
{
	m_spriteBatch = m_pResourceManager->GetSpriteBatch();
	m_titleTexture = m_pResourceManager->RequestDDSTexture("title.dds");
	m_backTexture = m_pResourceManager->RequestDDSTexture("titleback.dds");
	m_pressTexture = m_pResourceManager->RequestDDSTexture("pressspace.dds");
	m_model = m_pResourceManager->RequestModel("JumpinPlayer.sdkmesh");

	m_camera->Initialize({0,5.0f,10.0f});
	m_bgm->SetVolume(0.3f);
	m_bgm->Play(true);
}



/**
 * @brief �X�V����
 *
 * @param[in] inputDevice ���̓f�o�C�X
 *
 * @return �Ȃ�
 */
void TitleScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	// �V�[���̐؂�ւ�
	if (traker->pressed.Space) 
	{
		m_bgm->Stop();
		m_decideSound->Play(false);
		ChangeScene("StageSelect");
	}

	m_rotationY += DirectX::XMConvertToRadians(36.0f)*elapsedTime;

	m_camera->Update({0,2,0});
}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	DirectX::SimpleMath::Matrix world;
	//���s�ړ��s����쐬����
	DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation({0,-1,0});
	//Z���̉�]�s����쐬����
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotationY);
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
	world = scale * rotY * tras;
	//�r���[�s��擾
	DirectX::SimpleMath::Matrix view = m_camera->GetView();


	m_spriteBatch->Begin();

	m_spriteBatch->Draw(m_backTexture, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(150, 0));
	m_spriteBatch->Draw(m_pressTexture, DirectX::SimpleMath::Vector2(150, 600));
	
	m_spriteBatch->End();
	m_model->Draw(&context, states, world, view, proj);



}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Finalize()
{
	
}
