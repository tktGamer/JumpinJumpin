/**
 * @file   ResultScene.h
 *
 * @brief  ���U���g�V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"

#include"Game/Common/Sound.h"


// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief ���U���g�V�[��
 */
class ResultScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	DirectX::SpriteBatch* m_spriteBatch;    ///< �X�v���C�g�o�b�`
	ID3D11ShaderResourceView* m_resultTexture;	///< ���U���g�摜
	ID3D11ShaderResourceView* m_pressTexture;	///< �v���X�摜
	ID3D11ShaderResourceView* m_backTexture;	///< �w�i�摜

	bool m_isClear;	///< �N���A�������ǂ���
	std::unique_ptr<Sound> m_clearSound;///< �N���A��
	std::unique_ptr<Sound> m_gameoverSound;///< ���s��

	// �I�u�W�F�N�g�֘A
	


// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	ResultScene(SceneManager* pSceneManager, ResourceManager* pResourceManager);

	// �f�X�g���N�^
	~ResultScene();


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
