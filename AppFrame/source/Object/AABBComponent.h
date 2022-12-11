/*****************************************************************//**
 * \file   AABBComponent.h
 * \brief  親オブジェクトに追従するAABB
 * 
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
#include "../Utility/AABB.h"

	class AABBComponent :public ComponentBase
	{
	public:
		AABBComponent();
		~AABBComponent();
		bool Init()override;
		void Update()override;
		void Render()override;
		void Debug()override;
		void SetSizeX(float sizex) { _sizeX = sizex; }
		void SetSizeY(float sizez) { _sizeY = sizez; }
		AABB GetAABB() { return _collision; }
		void SetMovable(bool flag) { _movable = flag; }
		void SetXZaxis(bool flag) { _XZaxis = flag; };
	private:
		void UpdateCollision();
		bool _movable;
		float _sizeX, _sizeY;
		AABB _collision;
		bool _XZaxis;
	};