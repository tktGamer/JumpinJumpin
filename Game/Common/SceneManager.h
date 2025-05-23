#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include<memory>
#include<string>
#include<unordered_map>

class Scene;
class ResourceManager;

class SceneManager
{
	//�G�C���A�X�錾 ----------------------------------------------------
private:
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<Scene>>;
	using SharedData = std::unordered_map<std::string, std::string>;
	// �N���X�萔�̐錾 -------------------------------------------------
public:



	// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	SceneCollection m_scenes;//�V�[���Q

	Scene* m_pCurrentScene;//���݂̃V�[��
	Scene* m_pRequestedScene;//�ύX�v���̂������V�[��

	SharedData m_sharedData;//���L�f�[�^

	//�L�[�{�[�h�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_traker;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	SceneManager();

	// �f�X�g���N�^
	~SceneManager();


	// ����
public:
	// �V�[���̓o�^
	void Register(const std::string& sceneName, std::unique_ptr<Scene> scene);

	// �X�V����
	void Update(DirectX::Keyboard::State key, float elapsedTime);

	// �`�揈��
	void Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj);

	// �J�n�V�[���̐ݒ�
	void SetStratScene(const std::string& startSceneName);

	// �V�[���ύX�̗v��
	void RequestSceneChange(const std::string& nextSceneName);


	// �擾/�ݒ�
public:
	//���L�f�[�^�̎擾
	std::string GetSharedData(const std::string& key) const;

	//���L�f�[�^�̐ݒ�
	void SetSharedData(const std::string& key, const std::string& value);

	// ��������
private:
	//�V�[���̕ύX
	void ChangeScene();


};

