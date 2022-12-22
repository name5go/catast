/*****************************************************************//**
 * \file   CollisionComponent.h
 * \brief  球状コリジョン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
class  CollisionComponent :public ComponentBase
{
public:
	CollisionComponent();
	~CollisionComponent();
	bool Init()override;
	void Update()override;
	void Render()override;
	void Debug()override;
	bool Intersect( CollisionComponent& otherCollision);
	bool Intersect(int mv1Handle);

	void SetPosition(VECTOR value) { _position = value; }
	VECTOR GetPosition() { return _position; }
	void SetRadius(float value) { _radius = value; }
	float GetRadius() { return _radius; }
	void SetAttachFrame(int value) { _attachFrame = value; }
	int GetAttachFrame() { return _attachFrame; }
private:
	VECTOR _position;
	float _radius;
	int _attachFrame;//アタッチされているフレーム（ボーンの別称）
};
