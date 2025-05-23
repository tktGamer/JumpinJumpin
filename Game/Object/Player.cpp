// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Player.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Common/Sound.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Player::Player()
    : m_rotationZ{ 0.0f }
	, m_position{}
    ,m_model{}
    ,m_jumpSound{}
{
}

/**
 * @brief �f�X�g���N�^
 */
Player::~Player()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Player::Initialize(ResourceManager* pResourceManager)
{

   m_model = pResourceManager->RequestModel(L"JumpinPlayer.sdkmesh");
   m_jumpSound =std::make_unique<Sound>(pResourceManager->RequestSound("jump.wav"));
   m_position = { 0.0f,0.0f,0.0f };
   m_velocity = {};
   m_rotationZ = 0.0f;
   m_gravity.y = GRAVITY;
   DirectX::SimpleMath::Vector3 start = { m_position.x,m_position.y,m_position.z };
   DirectX::SimpleMath::Vector3 vector = {0.0f,3.5f,0.0f};
   m_capsuleCollider = CapsuleCollider{ start, vector,RADIUS};
}

/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime �t���[������
 *
 * @return �Ȃ�
 */
void Player::Update(float& elapsedTime, DirectX::Keyboard::KeyboardStateTracker* traker)
{

    if (traker->lastState.Left)
    {
        m_rotationZ += DirectX::XMConvertToRadians(120.0f)*elapsedTime;


    }
    if (traker->lastState.Right)
    {
        m_rotationZ -= DirectX::XMConvertToRadians(120.0f)*elapsedTime;
    }

	m_velocity += m_gravity*elapsedTime;
    m_position += m_velocity * elapsedTime;

	m_capsuleCollider.SetStart({ m_position.x,m_position.y,m_position.z });
	m_capsuleCollider.SetRotation({ 0.0f,0.0f,m_rotationZ });
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
void Player::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view,DirectX::SimpleMath::Matrix& proj)
{


    DirectX::SimpleMath::Matrix world;
    //���s�ړ��s����쐬����
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Z���̉�]�s����쐬����
    DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale * rotZ * tras;

	m_model->Draw(&context, states, world, view, proj);
}


/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Player::Finalize()
{
}


void Player::Jump()
{
    //Z���̉�]�s����쐬����
    DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    m_velocity = DirectX::SimpleMath::Vector3::Transform(JUMP, rotZ);
    m_jumpSound->Play(false);

}

DirectX::SimpleMath::Vector3 Player::GetPosition()
{
    return m_position;
}

CapsuleCollider Player::GetCollider() const
{
    return m_capsuleCollider;
}
