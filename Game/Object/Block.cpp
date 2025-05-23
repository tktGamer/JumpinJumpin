// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Block.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Block::Block()
	:m_model{}
    ,m_rotationZ{  }
	, m_collider{}
{
}

/**
 * @brief デストラクタ
 */
Block::~Block()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Block::Initialize(DirectX::Model* model, DirectX::SimpleMath::Vector3 position)
{
    m_model = model;
    m_position=position;
    m_rotationZ = 0.0f;

    m_collider = BoxCollider{m_position,LENGTH/2};
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime フレーム時間
 *
 * @return なし
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
    //プレイヤーの速度ベクトル
    DirectX::SimpleMath::Vector3 v(0.0f, 0.0f, 0.0f);
    //Y軸の回転行列を作成する
    DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    //指定された行列でベクトルを変換する
    v = DirectX::SimpleMath::Vector3::Transform(m_velocity, rotY);

    m_position += v * elapsedTime;

	m_collider.SetPosition(m_position);
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
void Block::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
    DirectX::SimpleMath::Matrix world;
    //平行移動行列を作成する
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Y軸の回転行列を作成する
    DirectX::SimpleMath::Matrix rotY= DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale *rotY * tras;

    m_model->Draw(&context, states, world, view, proj);

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
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
