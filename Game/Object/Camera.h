#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

class Camera
{
private:
	//��x�N�g��
	DirectX::SimpleMath::Vector3 m_up;
	//�J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

public:
	Camera();

	~Camera();

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update(DirectX::SimpleMath::Vector3 targetPos);


	void Finalize();

	void SetPosition(DirectX::SimpleMath::Vector3 position);
	void SetPositionX(float posX);
	void SetPositionY(float posY);
	void SetPositionZ(float posZ);

	DirectX::SimpleMath::Matrix GetView();
};

