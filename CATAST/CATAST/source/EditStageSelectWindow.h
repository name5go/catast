/*****************************************************************//**
 * \file   EditStageSelectWindow.h
 * \brief  編集するステージ数を選択するウィンドウ
 * 
 * \author 土居将太郎
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

