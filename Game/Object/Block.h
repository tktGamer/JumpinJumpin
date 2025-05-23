#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

#include"Game/Common/BoxCollider.h"

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class Block
{
public:
	static constexpr DirectX::SimpleMath::Vector3 LENGTH = {2.0f,2.0f,2.0f};
private:
	//�u���b�N�̃��f��
	DirectX::Model* m_model;
	//�u���b�N�̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;

	//�v���C���[�̌���(Z����]�F���W�A��)
	float m_rotationZ;

	BoxCollider m_collider;
public:
	Block();
	~Block();
	void Initialize(DirectX::Model* model,DirectX::SimpleMath::Vector3 position);
	void Update(float& elapsedTime, DirectX::Keyboard::State key);
	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	void Finalize();
	DirectX::SimpleMath::Vector3 GetPosition();
	BoxCollider GetCollider();
};

