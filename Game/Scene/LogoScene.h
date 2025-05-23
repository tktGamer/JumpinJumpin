/**
 * @file   LogoScene.h
 *
 * @brief  ���S�V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"




// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief ���S�V�[��
 */
class LogoScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//static constexpr SpriteAnimator::AnimationClip LOGO_CLIP =    ///< ���S�A�j���[�V�����̃N���b�v
	//{
	//	{0,0,640,480},    // �J�n�t���[���̗̈�[pixel]
	//	18,               // ���t���[����
	//	6,                // ��(�P�s������̃t���[����)
	//	9 * 14,           // �Đ�����[frames]
	//	false              // ���[�v�����邩�ǂ���
	//};



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	//�e�N�X�`��
	//int m_texture;
	//���S�̍��W
	//GameLib::Point2D m_spritePostion;
	////�V�[���J�ڋ���
	//bool m_change;
	//// ���\�[�X�֘A
	////�X�v���C�g
	//Sprite m_sprite;
	//SpriteAnimator m_spriteAnimator;


	// �I�u�W�F�N�g�֘A



// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	LogoScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// �f�X�g���N�^
	~LogoScene();


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
