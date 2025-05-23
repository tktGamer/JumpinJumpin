#pragma once
// ヘッダファイルの読み込み ===================================================

#include"Game/Object/Block.h"
#include"Game/Common/BoxCollider.h"
// クラスの定義 ===============================================================
/**
  * @brief ステージ
  */
class Goal
{
private:

	//ゴールのモデル
	DirectX::Model* m_goalModel;
	DirectX::SimpleMath::Vector3 m_position;

	BoxCollider m_collider;
public:
	Goal();
	~Goal();
	void Initialize(DirectX::Model* model, DirectX::SimpleMath::Vector3 position);
	void Update(float& elapsedTime);
	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	void Finalize();

	BoxCollider GetCollider();
};

