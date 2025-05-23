#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class BoxCollider
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum VectorIndex
	{
		X = 0,
		Y = 1,
		Z = 2,

		NUM
	};
// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_center; ///< 中心座標
	DirectX::SimpleMath::Vector3 m_halfSize; ///< 半分のサイズ
	DirectX::SimpleMath::Vector3 m_normaDirect[VectorIndex::NUM]; ///< 方向ベクトル
	DirectX::SimpleMath::Vector3 m_rotation; ///< 回転
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BoxCollider();
	BoxCollider(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Vector3 halfSize);

	// デストラクタ
	~BoxCollider();


// 操作
public:

	// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegOnSeparateAxis(DirectX::SimpleMath::Vector3* Sep, DirectX::SimpleMath::Vector3* e1, DirectX::SimpleMath::Vector3* e2, DirectX::SimpleMath::Vector3* e3 = 0) const;




	void SetPosition(const DirectX::SimpleMath::Vector3 pos);
	void SetRotation(const DirectX::SimpleMath::Vector3 rot);

	DirectX::SimpleMath::Vector3 GetPosition() const;
	DirectX::SimpleMath::Vector3 GetMin() const;
	DirectX::SimpleMath::Vector3 GetMax() const;

	
	//指定軸の方向ベクトルの取得
	DirectX::SimpleMath::Vector3 GetDirect(VectorIndex index) const;
	// 指定軸方向の長さを取得
	float GetLengthW(VectorIndex Index) const;          
};
	//OBB同士の衝突判定
	bool CollBox(const BoxCollider& OBB1, const BoxCollider& OBB2) ;
