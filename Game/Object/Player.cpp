// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Common/Sound.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Player::Player()
    : m_rotationZ{ 0.0f }
	, m_position{}
    ,m_model{}
    ,m_jumpSound{}
{
}

/**
 * @brief デストラクタ
 */
Player::~Player()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
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
 * @brief 更新処理
 *
 * @param[in] elapsedTime フレーム時間
 *
 * @return なし
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
 * @brief 描画処理
 *
 * @param[in] context
 * @param[in] states
 * @param[in] view
 * @param[in] proj
 *
 * @return なし
 */
void Player::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view,DirectX::SimpleMath::Matrix& proj)
{


    DirectX::SimpleMath::Matrix world;
    //平行移動行列を作成する
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Z軸の回転行列を作成する
    DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale * rotZ * tras;

	m_model->Draw(&context, states, world, view, proj);
}


/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Finalize()
{
}


void Player::Jump()
{
    //Z軸の回転行列を作成する
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
