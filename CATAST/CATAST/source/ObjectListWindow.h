/*****************************************************************//**
 * \file   ObjectListWindow.h
 * \brief  配置しているオブジェクトのリストを表示するUI 24個表示
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once

class ObjectListWindow : public ObjectBase
{
public:
	ObjectListWindow();
	void Init()override;
	void Update(InputManager& input)override;
	void Render()override;
	int GetSelectStage() { return _selectStage; }
	void SetSelectStage(int value) { _selectStage = value; }
	void SetSelectID(int value) { _selectID = value; }
	int GetSelectID() { return _selectID; }
	void ScrollUp();
	void ScrollDown();
private:
	int _gimmickNumber;
	int _scroll;
	int _selectStage;
	int _selectID;
	int _sizeX, _sizeY;
	std::unique_ptr<ObjectBase> _copy;
	template <typename T>
	void Copy(ObjectBase*);
	template <typename T>
	void Paste();
};
