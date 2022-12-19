/*****************************************************************//**
 * \file   AABB2DComponent.cpp
 * \brief  親オブジェクトに追従する2DのAABB
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#include "AABB2DComponent.h"
#include "ObjectBase.h"

AABB2DComponent::AABB2DComponent()
	:_sizeX{ 100 }
	, _sizeY{ 100 }
	, _movable{ true }
	, _XZaxis{ false }
	, _rootPositionCenter{ false }
{
}
AABB2DComponent::~AABB2DComponent()
{
}
bool AABB2DComponent::Init()
{
	UpdateCollision();
	return true;
}
void AABB2DComponent::Update()
{
	if (_movable) {
		UpdateCollision();
	}
}
void AABB2DComponent::Render()
{
}
void AABB2DComponent::Debug()
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
void AABB2DComponent::UpdateCollision()
{
	auto position = _parent->GetPosition();
	/*オブジェクトの位置取得*/
	Vector2 pos{ static_cast<double>(position.x),static_cast<double>(position.y) };
	if (_XZaxis) {
		Vector2 pos = { static_cast<double>(position.x),static_cast<double>(position.z) };
	}
	double minOffset{0.0};
	double maxOffset{ 1.0 };
	if (_rootPositionCenter) {
		double minOffset = 0.5;
		double maxOffset = 0.5;
	}

	_collision.min = { pos.x - _sizeX * minOffset,pos.y - _sizeY * minOffset };
	_collision.max = { pos.x + _sizeX * maxOffset,pos.y+ _sizeY * maxOffset };
}