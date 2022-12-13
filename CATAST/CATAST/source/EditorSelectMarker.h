/*****************************************************************//**
 * \file   EditorSelectMarker.h
 * \brief  選択した物体を示すマーカー
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ObjectListWindow;
class EditorSelectMarker : public ObjectBase
{
public:
	EditorSelectMarker(ObjectListWindow& list);
	void Update(InputManager& input)override;
	void Render()override;
private:
	ObjectListWindow& _list;
};

