#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class CapsuleCollider
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_start; ///<始点
	DirectX::SimpleMath::Vector3 m_vector; ///<方向ベクトル
	DirectX::SimpleMath::Vector3 m_rotation; ///<
	float m_radius; ///<半径
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	CapsuleCollider();
	CapsuleCollider(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float radius);

	// デストラクタ
	~CapsuleCollider();


// 操作
public:


//取得・設定
public:
	void SetStart(const DirectX::SimpleMath::Vector3 start);
	void SetVector(const DirectX::SimpleMath::Vector3 vector);
	void SetRotation(const DirectX::SimpleMath::Vector3 rot);
	DirectX::SimpleMath::Vector3 GetStart() const;
	DirectX::SimpleMath::Vector3 GetEnd() const;
	DirectX::SimpleMath::Vector3 GetVector() const;
	float GetRadius() const;
};
