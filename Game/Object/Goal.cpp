#include "pch.h"
#include "Goal.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Goal::Goal()
	: m_goalModel{}
	, m_collider{}
{
}

/**
 * @brief デストラクタ
 */
Goal::~Goal()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] model モデルのポインタ
 *
 * @return なし
 */
void Goal::Initialize(DirectX::Model* model, DirectX::SimpleMath::Vector3 position)
{
	m_goalModel = model;
	m_position = position;
	m_collider = BoxCollider(position, DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
}
/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime フレーム時間
 *
 * @return なし
 */
void Goal::Update(float& elapsedTime)
{
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
void Goal::Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
    DirectX::SimpleMath::Matrix world;
    //平行移動行列を作成する
    DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
    //Y軸の回転行列を作成する
    //DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotationZ);
    DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.0f);
    world = scale * tras;

    m_goalModel->Draw(&context, states, world, view, proj);

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Goal::Finalize()
{
}

BoxCollider Goal::GetCollider()
{
    return m_collider;
}
