/*****************************************************************//**
 * \file   AABBComponent.cpp
 * \brief  親オブジェクトに追従するAABB
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#include "AABBComponent.h"
#include "ObjectBase.h"

AABBComponent::AABBComponent()
	:_sizeX{ 100 }
	, _sizeY{ 100 }
	, _movable{ true }
	, _XZaxis{ false }
{
}
AABBComponent::~AABBComponent()
{
}
bool AABBComponent::Init()
{
	UpdateCollision();
	return true;
}
void AABBComponent::Update()
{
	if (_movable) {
		UpdateCollision();
	}
}
void AABBComponent::Render()
{
}
void AABBComponent::Debug()
{
	auto pos1 = _parent->GetPosition();
	pos1.x -= _sizeX / 2;
	pos1.z -= _sizeY / 2;
	auto pos2 = pos1;
	pos2.x += _sizeX;
	auto pos3 = pos1;
	pos3.z += _sizeY;
	auto pos4 = pos1;
	pos4.x += _sizeX;
	pos4.z += _sizeY;

	auto diffuseColor{ GetColorU8(255,255,255,255) };
	auto specularColor{ GetColorU8(0,0,0,0) };
	VERTEX3D vertex[4] = {
		{ pos1, {0,1.0f,0},diffuseColor, specularColor, 0, 1, 0, 0 },
		{ pos2, {0,1.0f,0}, diffuseColor, specularColor, 1, 1, 0, 0},
		{ pos3, {0,1.0f,0}, diffuseColor, specularColor, 0, 0, 0, 0 },
		{ pos4, {0,1.0f,0}, diffuseColor, specularColor, 1, 0, 0, 0 },
	};
	unsigned short indices[6] = { 0,1,2,1,3,2 };

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawCube3D(pos1, pos4, GetColor(255, 255, 255), GetColor(0, 0, 0), true);
	//DrawPolygonIndexed3D(vertex, 4, indices, 2, DX_NONE_GRAPH, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
void AABBComponent::UpdateCollision()
{
	auto Position = _parent->GetPosition();
	if (_XZaxis) {
		_collision.min = { Position.x - _sizeX / 2.0,Position.z - _sizeY / 2.0 };
		_collision.max = { Position.x + _sizeX / 2.0,Position.z + _sizeY / 2.0 };
	}
	else {
		_collision.min = { Position.x - _sizeX / 2.0,Position.y - _sizeY / 2.0 };
		_collision.max = { Position.x + _sizeX / 2.0,Position.y + _sizeY / 2.0 };
	}

}