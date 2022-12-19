/*****************************************************************//**
 * \file   AABBComponent.h
 * \brief  親オブジェクトに追従する2DのAABB
 * 
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
#include "../Utility/AABB2D.h"

	class AABB2DComponent :public ComponentBase
	{
	public:
		AABB2DComponent();
		~AABB2DComponent();
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
		bool _rootPositionCenter;
		bool _XZaxis;
	};