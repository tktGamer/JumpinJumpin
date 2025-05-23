/**
 * @file   GameScene.h
 *
 * @brief  �Q�[���V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"
#include "Game/Object/Player.h"
#include "Game/Object/Camera.h"
#include"Game/Object/Block.h"
#include"Game/Object/Stage.h"
#include"Game/Common/Sound.h"
// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief �Q�[���V�[��
 */
class GameScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:

	//��
	struct Circle
	{
		DirectX::SimpleMath::Vector3 pos;
		float radius;
	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	std::unique_ptr<Sound> m_gameBGM;
	std::unique_ptr<Sound> m_hitBlockSound;
	// �I�u�W�F�N�g�֘A
	std::unique_ptr<Player> m_player;    ///< �v���C���[�I�u�W�F�N�g
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	std::unique_ptr<Stage> m_stage;

	
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GameScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// �f�X�g���N�^
	~GameScene();


// ����
public:
	// ����������
	void Initialize() override;

	// �X�V����
	void Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime) override;

	// �`�揈��
	void Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj) override;

	// �I������
	void Finalize() override;


// �擾/�ݒ�
public:


// ��������
private:
	bool CapsuleToAABB(CapsuleCollider capsule, BoxCollider box);

	bool IsHit(Circle circle, BoxCollider box);
};
