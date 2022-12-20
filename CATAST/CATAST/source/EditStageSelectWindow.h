/*****************************************************************//**
 * \file   EditStageSelectWindow.h
 * \brief  �ҏW����X�e�[�W����I������E�B���h�E
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
class EditStageSelectWindow : public ObjectBase
{
public:
	EditStageSelectWindow(ObjectListWindow& list);
	void Update(InputManager&)override;
	void Render()override;
	void Debug()override;
	bool MessageEvent(ObjectBase*,std::string)override;
private:
	ObjectListWindow& _list;

	int _sizeX, _sizeY;
};

