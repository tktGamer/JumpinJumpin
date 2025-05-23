#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class CapsuleCollider
{
// �N���X�萔�̐錾 -------------------------------------------------
public:

// �f�[�^�����o�̐錾 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_start; ///<�n�_
	DirectX::SimpleMath::Vector3 m_vector; ///<�����x�N�g��
	DirectX::SimpleMath::Vector3 m_rotation; ///<
	float m_radius; ///<���a
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	CapsuleCollider();
	CapsuleCollider(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float radius);

	// �f�X�g���N�^
	~CapsuleCollider();


// ����
public:


//�擾�E�ݒ�
public:
	void SetStart(const DirectX::SimpleMath::Vector3 start);
	void SetVector(const DirectX::SimpleMath::Vector3 vector);
	void SetRotation(const DirectX::SimpleMath::Vector3 rot);
	DirectX::SimpleMath::Vector3 GetStart() const;
	DirectX::SimpleMath::Vector3 GetEnd() const;
	DirectX::SimpleMath::Vector3 GetVector() const;
	float GetRadius() const;
};
