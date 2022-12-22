/*****************************************************************//**
 * \file   CollisionComponent.cpp
 * \brief  ‹…óƒRƒŠƒWƒ‡ƒ“
 *
 * \author “y‹«‘¾˜Y
 * \date   December 2022
 *********************************************************************/

#include "CollisionComponent.h"
#include "MV1Component.h"
#include "ObjectBase.h"

CollisionComponent::CollisionComponent()
	: _position{ 0.0f,0.0f,0.0f }
	, _radius{ 8 }
	, _attachFrame{ -1 }
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::Init()
{
	_position = _parent->GetPosition();
	return true;
}

void CollisionComponent::Update()
{
	if (_attachFrame > 0) {
		if (_parent->GetComponent<MV1Component>() != nullptr) {
			auto handle = _parent->GetComponent<MV1Component>()->GetModelHandle();
			MV1GetFrameLocalWorldMatrix(handle, _attachFrame);
			return;
		}
	}
	_position=_parent->GetPosition();

}

void CollisionComponent::Render()
{
}

void CollisionComponent::Debug()
{
	DrawSphere3D(_position, _radius, 12, GetColor(255, 255, 0), GetColor(0, 0, 0), false);

}

bool CollisionComponent::Intersect(CollisionComponent& otherCollision)
{
	auto dif = VSub(otherCollision.GetPosition(), _position);
	auto otherRadius = otherCollision.GetRadius();
	if (dif.x * dif.x + dif.y * dif.y + dif.z * dif.z <= (_radius + otherRadius) * (_radius + otherRadius)) {
		return true;
	}
	return false;
}

bool CollisionComponent::Intersect(int mv1Handle)
{
	MV1SetupCollInfo(mv1Handle, -1);
	auto hitResult = MV1CollCheck_Sphere(mv1Handle, -1, _position, _radius);
	if (hitResult.HitNum > 0) {
		MV1CollResultPolyDimTerminate(hitResult);
		return true;
	}
	MV1CollResultPolyDimTerminate(hitResult);
	return false;
}
