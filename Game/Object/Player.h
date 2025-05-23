#pragma once
// ヘッダファイルの読み込み ===================================================
class Sound;
class ResourceManager;
#include"Game/Common/CapsuleCollider.h"
// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class Player
{
private:
	static constexpr DirectX::SimpleMath::Vector3 JUMP = { 0.0f,14.0f,0.0f };
	static constexpr float GRAVITY = -15.7f;
	static constexpr float RADIUS = 1.0f;
private:
	//プレイヤーのモデル
	DirectX::Model* m_model;
	//プレイヤーの位置
	DirectX::SimpleMath::Vector3 m_position;
	//速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//プレイヤーの向き(Z軸回転：ラジアン)
	float m_rotationZ;

	//プレイヤーの当たり判定
	CapsuleCollider m_capsuleCollider;
	//重力
	DirectX::SimpleMath::Vector3 m_gravity;

	//ジャンプ音
	std::unique_ptr<Sound> m_jumpSound;
public:
	Player();

	~Player();

	void Initialize(ResourceManager* pResourceManager);

	void Update(float& elapsedTime, DirectX::Keyboard::KeyboardStateTracker* traker);

	void Draw(ID3D11DeviceContext& context, DirectX::DX11::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void Finalize();

	//bool IsHit(Circle& circle);

	void Jump();

	DirectX::SimpleMath::Vector3 GetPosition();
	CapsuleCollider GetCollider() const;
};

