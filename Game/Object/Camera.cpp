// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Camera.h"

using namespace DirectX;

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Camera::Camera()
    :m_up{0.0f,1.0f,0.0f}
    ,m_view{}
{
}

Camera::~Camera()
{
}


/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Camera::Initialize(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
    m_up={ 0.0f,1.0f,0.0f };

}

/**
 * @brief �X�V����
 *
 * @param[in] 
 *
 * @return �Ȃ�
 */
void Camera::Update(DirectX::SimpleMath::Vector3 targetPos)
{
    //�����ō쐬�����r���[�s��Őݒ肷��
    m_view = SimpleMath::Matrix::CreateLookAt(
        m_position,       //�J�����̈ʒu
        targetPos,       //�^�[�Q�b�g�̈ʒu
        m_up);               //�J�����̏�x�N�g��

}

/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Camera::Finalize()
{
}

void Camera::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
}

void Camera::SetPositionX(float posX)
{
	m_position.x = posX;
}

void Camera::SetPositionY(float posY)
{
	m_position.y = posY;
}

void Camera::SetPositionZ(float posZ)
{
	m_position.z = posZ;
}

DirectX::SimpleMath::Matrix Camera::GetView()
{
    return m_view;
}
