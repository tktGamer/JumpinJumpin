// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Block.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Block::Block()
	:m_model{}
    ,m_rotationZ{  }
	, m_collider{}
{
}

/**
 * @brief �f�X�g���N�^
 */
Block::~Block()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Block::Initialize(DirectX::Model* model, DirectX::SimpleMath::Vector3 position)
{
    m_model = model;
    m_position=position;
    m_rotationZ = 0.0f;

    m_collider = BoxCollider{m_position,LENGTH/2};
}

/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime �t���[������
 *
 * @return �Ȃ�
 */
void Block::Update(float& elapsedTime, DirectX::Keyboard::State key)
{
	m_velocity = { 0.0f, 0.0f, 0.0f };
    if (key.Left)
    {
        m_rotationZ += DirectX::XMConvertToRadians(1.0f);
    }
    if (key.Right)
    {
        m_rotationZ -= DirectX::XMConvertToRadians(1.0f);
    }

    if (key.Up)
    {
        m_velocity.y += 0.8f;
    }
    if (key.Down)
    {
        m_velocity.y -= 0.8f;

    }

    if (m_position.y <= 0.0f)
    {
        //m_velocity.y += JUMP;
    }

    //m_velocity.y += m_gravity;
    //�v���C���[�̑��x�x�N�g��
    DirectX::SimpleMath::Vector3 v(0.0f, 0.0f, 0.0f);
    //Y���̉�]�s����쐬����
    DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    //�w�肳�ꂽ�s��Ńx�N�g����ϊ�����
    v = DirectX::SimpleMath::Vector3::Transform(m_velocity, rotY);

    m_position += v * elapsedTime;

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
void Block::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
    DirectX::SimpleMath::Matrix world;
    //���s�ړ��s����쐬����
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Y���̉�]�s����쐬����
    DirectX::SimpleMath::Matrix rotY= DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale *rotY * tras;

    m_model->Draw(&context, states, world, view, proj);

}

/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Block::Finalize()
{
}

DirectX::SimpleMath::Vector3 Block::GetPosition()
{
    return m_position;
}

BoxCollider Block::GetCollider()
{
    return m_collider;
}
