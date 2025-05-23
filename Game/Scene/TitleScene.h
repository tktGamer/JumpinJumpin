/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"
#include"Game/Object/Camera.h"
#include"Game/Common/Sound.h"


// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief �^�C�g���V�[��
 */
class TitleScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	DirectX::SpriteBatch* m_spriteBatch;    ///< �X�v���C�g�o�b�`
	ID3D11ShaderResourceView* m_titleTexture;	///< �^�C�g���摜
	ID3D11ShaderResourceView* m_backTexture;	///< �w�i�摜
	ID3D11ShaderResourceView* m_pressTexture;	
	float m_rotationY;    ///< ��]�p�x
	// �I�u�W�F�N�g�֘A
	DirectX::Model* m_model;    ///< ���f��
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	std::unique_ptr<Sound> m_decideSound;
	std::unique_ptr<Sound> m_bgm;

	//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_traker;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	TitleScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// �f�X�g���N�^
	~TitleScene();


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


};
