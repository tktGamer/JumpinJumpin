#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class BoxCollider
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	enum VectorIndex
	{
		X = 0,
		Y = 1,
		Z = 2,

		NUM
	};
// �f�[�^�����o�̐錾 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_center; ///< ���S���W
	DirectX::SimpleMath::Vector3 m_halfSize; ///< �����̃T�C�Y
	DirectX::SimpleMath::Vector3 m_normaDirect[VectorIndex::NUM]; ///< �����x�N�g��
	DirectX::SimpleMath::Vector3 m_rotation; ///< ��]
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	BoxCollider();
	BoxCollider(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Vector3 halfSize);

	// �f�X�g���N�^
	~BoxCollider();


// ����
public:

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(DirectX::SimpleMath::Vector3* Sep, DirectX::SimpleMath::Vector3* e1, DirectX::SimpleMath::Vector3* e2, DirectX::SimpleMath::Vector3* e3 = 0) const;




	void SetPosition(const DirectX::SimpleMath::Vector3 pos);
	void SetRotation(const DirectX::SimpleMath::Vector3 rot);

	DirectX::SimpleMath::Vector3 GetPosition() const;
	DirectX::SimpleMath::Vector3 GetMin() const;
	DirectX::SimpleMath::Vector3 GetMax() const;

	
	//�w�莲�̕����x�N�g���̎擾
	DirectX::SimpleMath::Vector3 GetDirect(VectorIndex index) const;
	// �w�莲�����̒������擾
	float GetLengthW(VectorIndex Index) const;          
};
	//OBB���m�̏Փ˔���
	bool CollBox(const BoxCollider& OBB1, const BoxCollider& OBB2) ;
