/*****************************************************************//**
 * \file   EditorCamera.h
 * \brief  エディター使用時のカメラ
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once

class EditorCamera : public ObjectBase
{
public:
	EditorCamera(ObjectListWindow& list);
	~EditorCamera();
	void Init()override;
	void Update(InputManager& input)override;
	void Render()override;
	void Debug()override;
private:
	ObjectListWindow& _list;

	int _light;
};

