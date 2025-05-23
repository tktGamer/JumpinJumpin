/**
 * @file   GameScene.cpp
 *
 * @brief  �Q�[���V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "GameScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
GameScene::GameScene(SceneManager* pSceneManager, ResourceManager* pResourceManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{ pResourceManager }
	, m_player{}
	, m_camera{}
{
	m_player = std::make_unique<Player>();
	m_camera = std::make_unique<Camera>();
	m_stage = std::make_unique<Stage>();
	m_gameBGM = std::make_unique<Sound>(m_pResourceManager->RequestSound("gamebgm.wav"));
	m_hitBlockSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("death.wav"));
}



/**
 * @brief �f�X�g���N�^
 */
GameScene::~GameScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameScene::Initialize()
{
	int stageType;
	ReadSharedData("stage",&stageType);
	m_player->Initialize(m_pResourceManager);
	m_camera->Initialize({0,3,50.0f});
	m_stage->Initialize(m_pResourceManager,stageType);
	m_gameBGM->SetVolume(0.5f);
	m_gameBGM->Play(true);
}



/**
 * @brief �X�V����
 *
 * @param[in] inputDevice ���̓f�o�C�X
 *
 * @return �Ȃ�
 */
void GameScene::Update(DirectX::Keyboard::KeyboardStateTracker* traker, float elapsedTime)
{

	m_stage->Update(elapsedTime);
	m_player->Update(elapsedTime, traker);
	DirectX::SimpleMath::Vector3 targetPos = { m_player->GetPosition().x,3.0f,m_player->GetPosition().z};
	m_camera->Update(targetPos);
	m_camera->SetPositionX(m_player->GetPosition().x);


	std::vector <std::unique_ptr<Block>> & block = m_stage->GetBlock();

	for (std::unique_ptr<Block>& target : block)
	{
		//�����蔻��
		CapsuleCollider capsule = m_player->GetCollider();
		if (IsHit({ capsule.GetStart(),capsule.GetRadius() }, target->GetCollider())) 
		{
			m_player->Jump();
		}
		if (IsHit({ capsule.GetEnd(),capsule.GetRadius() }, target->GetCollider())) 
		{
			//�Q�[���I�[�o�[
			m_hitBlockSound->Play(false);
			m_gameBGM->Stop();
			WriteSharedData("result", false);
			ChangeScene("Result");
		}
	}

	Goal* pGoal = m_stage->GetGoal();
	//�����蔻��
	if (CapsuleToAABB(m_player->GetCollider(), pGoal->GetCollider()))
	{
		m_gameBGM->Stop();
		WriteSharedData("result", true);
		ChangeScene("Result");
	}
}



/**
 * @brief �`�揈��
 *
 * @param[in] context
 * @param[in] states
 * @param[in] proj
 *
 * @return �Ȃ�
 */
void GameScene::Render(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& proj)
{
	//�r���[�s��擾
	DirectX::SimpleMath::Matrix view = m_camera->GetView();
	m_stage->Draw(context, states, view, proj);
	m_player->Draw(context, states, view, proj);
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameScene::Finalize()
{
	m_player->Finalize();
	m_stage->Finalize();

}


/**
 * @brief �J�v�Z���ƃ{�b�N�X�̓����蔻��
 *
 * @param[in] capsule �J�v�Z��
 * @param[in] box	 �{�b�N�X
 *
 * @return true:�������Ă���
		   false:�������Ă��Ȃ�
 */
bool GameScene::CapsuleToAABB(CapsuleCollider capsule, BoxCollider box)
{
	//������Ȃ�����Ƃ肠��������AABB
	DirectX::SimpleMath::Vector3 min = box.GetMin();
	DirectX::SimpleMath::Vector3 max = box.GetMax();
	DirectX::SimpleMath::Vector3 center = capsule.GetStart();
	float radius = capsule.GetRadius();
	// AABB�̍ł��߂��_���v�Z
	float x = std::max(min.x, std::min(center.x, max.x));
	float y = std::max(min.y, std::min(center.y, max.y));
	float z = std::max(min.z, std::min(center.z, max.z));

	// ���̒��S�ƍł��߂��_�Ƃ̋����̓����v�Z
	float distanceSquared = (x - center.x) * (x - center.x) +
		(y - center.y) * (y - center.y) +
		(z - center.z) * (z - center.z);

	// �����̓�悪���̔��a�̓��ȉ��ł���Γ�����
	return distanceSquared <= (radius * radius);
}



/**
 * @brief ���ƃ{�b�N�X�̓����蔻��
 *
 * @param[in] circle ��
 * @param[in] box	 �{�b�N�X
 *
 * @return true:�������Ă���
		   false:�������Ă��Ȃ�
 */
bool GameScene::IsHit(Circle circle, BoxCollider box)
{
	//����AABB
	DirectX::SimpleMath::Vector3 min = box.GetMin();
	DirectX::SimpleMath::Vector3 max = box.GetMax();
	DirectX::SimpleMath::Vector3 center = circle.pos;
	float radius = circle.radius;
	// AABB�̍ł��߂��_���v�Z
	float x = std::max(min.x, std::min(center.x, max.x));
	float y = std::max(min.y, std::min(center.y, max.y));
	float z = std::max(min.z, std::min(center.z, max.z));

	// ���̒��S�ƍł��߂��_�Ƃ̋����̓����v�Z
	float distanceSquared = (x - center.x) * (x - center.x) +
		(y - center.y) * (y - center.y) +
		(z - center.z) * (z - center.z);

	// �����̓�悪���̔��a�̓��ȉ��ł���Γ�����
	return distanceSquared <= (radius * radius);
}
