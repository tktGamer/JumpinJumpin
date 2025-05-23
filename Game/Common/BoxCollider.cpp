#include "pch.h"
#include "BoxCollider.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 halfSize)
	:m_center{ center }
    , m_halfSize{ halfSize }
{
}

/**
 * @brief デストラクタ
 */
BoxCollider::~BoxCollider()
{
}


float BoxCollider::LenSegOnSeparateAxis(DirectX::SimpleMath::Vector3* Sep, DirectX::SimpleMath::Vector3* e1, DirectX::SimpleMath::Vector3* e2, DirectX::SimpleMath::Vector3* e3) const
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = std::abs(Sep->Dot(*e1));
	float r2 = std::abs(Sep->Dot(*e2));
	float r3 = e3 ? (std::abs(Sep->Dot(*e3))) : 0;
	return r1 + r2 + r3;
}

DirectX::SimpleMath::Vector3 BoxCollider::GetDirect(VectorIndex index) const
{

    switch (index)
    {
    case BoxCollider::X:
        break;
    case BoxCollider::Y:
        break;
    case BoxCollider::Z:
        break;
    case BoxCollider::NUM:
        break;
    default:
        break;
    }
    return DirectX::SimpleMath::Vector3();
}

/**
 * @brief ワールド座標系での指定軸方向の長さを取得
 *
 * @param[in] 
 *
 * @return 
 */
float BoxCollider::GetLengthW(VectorIndex Index) const
{
    switch (Index)
    {
    case BoxCollider::X:
		return m_halfSize.x;
        break;
    case BoxCollider::Y:
		return m_halfSize.y;
        break;
    case BoxCollider::Z:
		return m_halfSize.z;
        break;
    case BoxCollider::NUM:
        break;
    default:
        break;
    }
    return 0.0f;
}


void BoxCollider::SetPosition(const DirectX::SimpleMath::Vector3 pos)
{
	m_center = pos;
}

void BoxCollider::SetRotation(const DirectX::SimpleMath::Vector3 rot)
{
	m_rotation = rot;

}


DirectX::SimpleMath::Vector3 BoxCollider::GetPosition() const
{
    return m_center;
}

DirectX::SimpleMath::Vector3 BoxCollider::GetMin() const
{
    return m_center-m_halfSize;
}

DirectX::SimpleMath::Vector3 BoxCollider::GetMax() const
{
    return m_center+m_halfSize;
}

bool CollBox(const BoxCollider& OBB1, const BoxCollider& OBB2)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    DirectX::SimpleMath::Vector3 NAe1 = OBB1.GetDirect(BoxCollider::VectorIndex::X), Ae1 = NAe1 * OBB1.GetLengthW(BoxCollider::VectorIndex::X);
    DirectX::SimpleMath::Vector3 NAe2 = OBB1.GetDirect(BoxCollider::VectorIndex::Y), Ae2 = NAe2 * OBB1.GetLengthW(BoxCollider::VectorIndex::Y);
    DirectX::SimpleMath::Vector3 NAe3 = OBB1.GetDirect(BoxCollider::VectorIndex::Z), Ae3 = NAe3 * OBB1.GetLengthW(BoxCollider::VectorIndex::Z);
    DirectX::SimpleMath::Vector3 NBe1 = OBB2.GetDirect(BoxCollider::VectorIndex::X), Be1 = NBe1 * OBB2.GetLengthW(BoxCollider::VectorIndex::X);
    DirectX::SimpleMath::Vector3 NBe2 = OBB2.GetDirect(BoxCollider::VectorIndex::Y), Be2 = NBe2 * OBB2.GetLengthW(BoxCollider::VectorIndex::Y);
    DirectX::SimpleMath::Vector3 NBe3 = OBB2.GetDirect(BoxCollider::VectorIndex::Z), Be3 = NBe3 * OBB2.GetLengthW(BoxCollider::VectorIndex::Z);
    DirectX::SimpleMath::Vector3 Interval = OBB1.GetPosition() - OBB2.GetPosition();

    // 分離軸 : Ae1
    float rA = Ae1.Length();
    float rB = OBB1.LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    float L = std::abs(Interval.Dot(NAe1));
    if (L > rA + rB)
        return false; // 衝突していない

    // 分離軸 : Ae2
    rA = Ae2.Length();
    rB = OBB1.LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = std::abs(Interval.Dot(NAe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Ae3
    rA = Ae3.Length();
    rB = OBB1.LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = std::abs(Interval.Dot(NAe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be1
    rA = OBB1.LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = Be1.Length();
    L = std::abs(Interval.Dot(NBe1));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be2
    rA = OBB1.LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = Be2.Length();
    L = std::abs(Interval.Dot(NBe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be3
    rA = OBB1.LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = Be3.Length();
    L = std::abs(Interval.Dot(NBe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : C11
    DirectX::SimpleMath::Vector3 Cross;
    Cross = NAe1.Cross(NBe1);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C12
    Cross = NAe1.Cross(NBe2);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C13
    Cross = NAe1.Cross(NBe3);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C21
    Cross = NAe2.Cross(NBe1);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C22
    Cross = NAe2.Cross(NBe2);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C23
    Cross = NAe2.Cross(NBe3);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C31
    Cross = NAe3.Cross(NBe1);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C32
    Cross = NAe3.Cross(NBe2);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C33
    Cross = NAe3.Cross(NBe3);
    rA = OBB1.LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = OBB1.LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = std::abs(Interval.Dot(Cross));
    if (L > rA + rB)
        return false;

    // 分離平面が存在しないので「衝突している」
    return true;
}
