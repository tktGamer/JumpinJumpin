// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Scene.h"
#include"Game//Common/SceneManager.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Scene::Scene(SceneManager* pSceneManager)
	:m_pSceneManager{pSceneManager}
{
}

/**
 * @brief �f�X�g���N�^
 */
Scene::~Scene()
{
}


/**
 * @brief �V�[���̕ύX
 *
 * @param[in] nextSceneName�@�ύX��̃V�[��
 *
 * @return �Ȃ�
 */
void Scene::ChangeScene(const std::string& nextSceneName)
{
	m_pSceneManager->RequestSceneChange(nextSceneName);
}


/**
 * @brief ���L�f�[�^�̓ǂݍ���
 *
 * @param[in] key�@   ���L�f�[�^�̃L�[
 * @param[in] pValue�@�ǂݍ��ݐ�
 *
 * @return �Ȃ�
 */
void Scene::ReadSharedData(const std::string& key, int* pValue) const
{
	*pValue = std::stoi(m_pSceneManager->GetSharedData(key));
}

void Scene::ReadSharedData(const std::string& key, float* pValue) const
{
	*pValue = std::stof(m_pSceneManager->GetSharedData(key));
}

void Scene::ReadSharedData(const std::string& key, std::string* pValue) const
{
	*pValue = m_pSceneManager->GetSharedData(key);

}

void Scene::ReadSharedData(const std::string& key, bool* pValue) const
{
	*pValue = std::stoi(m_pSceneManager->GetSharedData(key));
}

/**
 * @brief ���L�f�[�^�̏�������
 *
 * @param[in] key�@   ���L�f�[�^�̃L�[
 * @param[in] value�@ �������ޒl
 *
 * @return �Ȃ�
 */
void Scene::WriteSharedData(const std::string& key, int value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));
}

void Scene::WtiteSharedData(const std::string& key, float value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));

}

void Scene::WriteSharedData(const std::string& key, std::string value) const
{
	m_pSceneManager->SetSharedData(key, value);

}

void Scene::WriteSharedData(const std::string& key, bool value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));
}

