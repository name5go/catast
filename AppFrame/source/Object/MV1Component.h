/*****************************************************************//**
 * \file   MV1Component.h
 * \brief  MV1のトランスフォーム更新、描画、アニメーションフレームの進行機能
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
	class AnimationComponent;
	class MV1Component :public ComponentBase
	{
	public:
		MV1Component(int modelHandle);
		~MV1Component();
		bool Init()override;
		void Update()override;
		void Render()override;
		void Debug()override;
		void SetModelHandle(int modelHandle) { _modelHandle = modelHandle; }
		int GetModelHandle() { return _modelHandle; }
		void SetAnimation(int index);
	private:
		int _modelHandle;
		int _attahIndex;
		float _playTime, _totalTime;
	};