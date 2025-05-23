#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
class Sound;
class ResourceManager;
#include"Game/Common/CapsuleCollider.h"
// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class Player
{
private:
	static constexpr DirectX::SimpleMath::Vector3 JUMP = { 0.0f,14.0f,0.0f };
	static constexpr float GRAVITY = -15.7f;
	static constexpr float RADIUS = 1.0f;
private:
	//�v���C���[�̃��f��
	DirectX::Model* m_model;
	//�v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//�v���C���[�̌���(Z����]�F���W�A��)
	float m_rotationZ;

	//�v���C���[�̓����蔻��
	CapsuleCollider m_capsuleCollider;
	//�d��
	DirectX::SimpleMath::Vector3 m_gravity;

	//�W�����v��
	std::unique_ptr<Sound> m_jumpSound;
public:
	Player();

	~Player();

	void Initialize(ResourceManager* pResourceManager);

	void Update(float& elapsedTime, DirectX::Keyboard::KeyboardStateTracker* traker);

	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void Finalize();

	//bool IsHit(Circle& circle);

	void Jump();

	DirectX::SimpleMath::Vector3 GetPosition();
	CapsuleCollider GetCollider() const;
};

