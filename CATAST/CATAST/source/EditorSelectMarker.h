/*****************************************************************//**
 * \file   EditorSelectMarker.h
 * \brief  �I���������̂������}�[�J�[
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once

class EditorSelectMarker : public ObjectBase
{
public:
	EditorSelectMarker(ObjectListWindow& list);
	void Update(InputManager& input)override;
	void Render()override;
private:
	ObjectListWindow& _list;
};

