#pragma once
// ヘッダファイルの読み込み ===================================================

class Camera
{
private:
	//上ベクトル
	DirectX::SimpleMath::Vector3 m_up;
	//カメラの位置
	DirectX::SimpleMath::Vector3 m_position;
	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;

public:
	Camera();

	~Camera();

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update(DirectX::SimpleMath::Vector3 targetPos);


	void Finalize();

	void SetPosition(DirectX::SimpleMath::Vector3 position);
	void SetPositionX(float posX);
	void SetPositionY(float posY);
	void SetPositionZ(float posZ);

	DirectX::SimpleMath::Matrix GetView();
};

