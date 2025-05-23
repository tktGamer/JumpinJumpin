#pragma once
// ヘッダファイルの読み込み ===================================================

#include"Game/Common/BoxCollider.h"

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class Block
{
public:
	static constexpr DirectX::SimpleMath::Vector3 LENGTH = {2.0f,2.0f,2.0f};
private:
	//ブロックのモデル
	DirectX::Model* m_model;
	//ブロックの位置
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;

	//プレイヤーの向き(Z軸回転：ラジアン)
	float m_rotationZ;

	BoxCollider m_collider;
public:
	Block();
	~Block();
	void Initialize(DirectX::Model* model,DirectX::SimpleMath::Vector3 position);
	void Update(float& elapsedTime, DirectX::Keyboard::State key);
	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	void Finalize();
	DirectX::SimpleMath::Vector3 GetPosition();
	BoxCollider GetCollider();
};

