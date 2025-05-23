#include "pch.h"
#include "Goal.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Goal::Goal()
	: m_goalModel{}
	, m_collider{}
{
}

/**
 * @brief �f�X�g���N�^
 */
Goal::~Goal()
{
}

/**
 * @brief ����������
 *
 * @param[in] model ���f���̃|�C���^
 *
 * @return �Ȃ�
 */
void Goal::Initialize(DirectX::Model* model, DirectX::SimpleMath::Vector3 position)
{
	m_goalModel = model;
	m_position = position;
	m_collider = BoxCollider(position, DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
}
/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime �t���[������
 *
 * @return �Ȃ�
 */
void Goal::Update(float& elapsedTime)
{
	m_collider.SetPosition(m_position);
}

/**
 * @brief �`�揈��
 *
 * @param[in] context
 * @param[in] states
 * @param[in] view
 * @param[in] proj
 *
 * @return �Ȃ�
 */
void Goal::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
    DirectX::SimpleMath::Matrix world;
    //���s�ړ��s����쐬����
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Y���̉�]�s����쐬����
    //DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale * tras;

    m_goalModel->Draw(&context, states, world, view, proj);

}

/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Goal::Finalize()
{
}

BoxCollider Goal::GetCollider()
{
    return m_collider;
}
