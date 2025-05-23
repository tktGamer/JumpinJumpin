#include "pch.h"
#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider()
{
}

CapsuleCollider::CapsuleCollider(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 vector, float radius)
	: m_start{ start }
	, m_vector{ vector }
	, m_radius{ radius }
{
}

CapsuleCollider::~CapsuleCollider()
{
}

void CapsuleCollider::SetStart(const DirectX::SimpleMath::Vector3 start)
{
	m_start = start;
}

void CapsuleCollider::SetVector(const DirectX::SimpleMath::Vector3 vector)
{
	m_vector = vector;
}

void CapsuleCollider::SetRotation(const DirectX::SimpleMath::Vector3 rot)
{
	m_rotation = rot;
}

DirectX::SimpleMath::Vector3 CapsuleCollider::GetStart() const
{
	return m_start;
}

DirectX::SimpleMath::Vector3 CapsuleCollider::GetEnd() const
{
	DirectX::SimpleMath::Vector3 vector;
	DirectX::SimpleMath::Matrix rot;
	rot= DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotation.z);
	vector = DirectX::SimpleMath::Vector3::Transform(m_vector, rot);
	rot = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation.y);
	vector = DirectX::SimpleMath::Vector3::Transform(vector, rot);
	rot = DirectX::SimpleMath::Matrix::CreateRotationX(m_rotation.x);
	vector = DirectX::SimpleMath::Vector3::Transform(vector, rot);
	return m_start +vector;
}

DirectX::SimpleMath::Vector3 CapsuleCollider::GetVector() const
{
	return m_vector;
}

float CapsuleCollider::GetRadius() const
{
	return m_radius;
}
