// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Camera.h"

using namespace DirectX;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
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
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Camera::Initialize(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
    m_up={ 0.0f,1.0f,0.0f };

}

/**
 * @brief 更新処理
 *
 * @param[in] 
 *
 * @return なし
 */
void Camera::Update(DirectX::SimpleMath::Vector3 targetPos)
{
    //自分で作成したビュー行列で設定する
    m_view = SimpleMath::Matrix::CreateLookAt(
        m_position,       //カメラの位置
        targetPos,       //ターゲットの位置
        m_up);               //カメラの上ベクトル

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
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
