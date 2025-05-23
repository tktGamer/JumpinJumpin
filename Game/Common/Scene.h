#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"pch.h"
#include <string>

class SceneManager;


// �N���X�̒�` ===============================================================
/**
  * @brief �V�[���̊��N���X
  */
class Scene
{
	// �N���X�萔�̐錾 -------------------------------------------------
public:



	// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	SceneManager* m_pSceneManager;

	// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Scene(SceneManager* m_pSceneManager);

	// �f�X�g���N�^
	virtual ~Scene();


	// ����
public:
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime) = 0;

	// �`�揈��
	virtual void Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj) = 0;

	// �I������
	virtual void Finalize() = 0;


	// �擾/�ݒ�
public:


	// ��������
protected:
	//�V�[���̕ύX
	void ChangeScene(const std::string& nextSceneName);

	//���L�f�[�^�̓ǂݍ���
	void ReadSharedData(const std::string& key, int* pValue) const;
	void ReadSharedData(const std::string& key, float* pValue) const;
	void ReadSharedData(const std::string& key, std::string* pValue) const;
	void ReadSharedData(const std::string& key, bool* pValue) const;

	//���L�f�[�^�̓ǂݍ���
	void WriteSharedData(const std::string& key, int		 value) const;
	void WtiteSharedData(const std::string& key, float		 value) const;
	void WriteSharedData(const std::string& key, std::string value) const;
	void WriteSharedData(const std::string& key, bool value) const;


};

