#pragma once
#include "appframe.h"
class ObjectListWindow;
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

