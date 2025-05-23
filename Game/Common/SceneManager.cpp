// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Common/SceneManager.h"
#include"Game//Common/Scene.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
SceneManager::SceneManager()
	:m_scenes{}
	, m_pCurrentScene{ nullptr }
	, m_pRequestedScene{ nullptr }
	, m_sharedData{}
	, m_traker{}
{
	m_traker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
}



/**
 * @brief �f�X�g���N�^
 */
SceneManager::~SceneManager()
{

}

/**
 * @brief �V�[���̓o�^
 *
 * @param[in] sceneName�@�V�[���̓o�^��
 * @param[in] scene�@�o�^�V�[��
 *
 * @return �Ȃ�
 */
void SceneManager::Register(const std::string& sceneName, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/**
 * @brief �X�V����
 *
 * @param[in] key		 �@���̓f�o�C�X
 * @param[in] elapsedTime�@�t���[���o�ߎ���
 *
 * @return �Ȃ�
 */
void SceneManager::Update(DirectX::Keyboard::State key, float elapsedTime)
{
	m_traker->Update(key);
	//�V�[���ύX���K�v���ǂ������`�F�b�N
	if (m_pRequestedScene != nullptr)
	{
		ChangeScene();
	}

	//���݂̃V�[�����X�V
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Update(m_traker.get(), elapsedTime);
	}
}

/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void SceneManager::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	//���݂̃V�[����`��
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Render(context,states,proj);
	}

}

/**
 * @brief �J�n�V�[���̐ݒ�
 *
 * @param[in] startSceneName�@�J�n�V�[����
 *
 * @return �Ȃ�
 */
void SceneManager::SetStratScene(const std::string& startSceneName)
{
	if (m_scenes.count(startSceneName) == 0)
	{
		return;
	}
	m_pCurrentScene = m_scenes[startSceneName].get();
	m_pCurrentScene->Initialize();
}

/**
 * @brief �V�[���ύX�̗v��
 *
 * @param[in] requestSceneName�@�ύX�\��̃V�[����
 *
 * @return �Ȃ�
 */
void SceneManager::RequestSceneChange(const std::string& nextSceneName)
{
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
}

/**
 * @brief ���L�f�[�^�̎擾
 *
 * @param[in] key�@�擾���������L�f�[�^�̃L�[
 *
 * @return �L�[���L�f�[�^
 */
std::string SceneManager::GetSharedData(const std::string& key) const
{
	if (m_sharedData.count(key) == 0)
	{
		return std::string{};
	}
	return m_sharedData.at(key);
}

/**
 * @brief ���L�f�[�^�̐ݒ�
 *
 * @param[in] key�@  �ݒ肵�������L�f�[�^�̃L�[
 * @param[in] vlaue�@�ݒ肵�������L�f�[�^�̒l
 *
 * @return �Ȃ�
 */
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_sharedData[key] = value;
}

/**
 * @brief �V�[���̕ύX
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}

	if (m_pCurrentScene)
	{
		m_pCurrentScene->Finalize();
	}

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();

	m_pRequestedScene = nullptr;
}



