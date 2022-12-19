/*****************************************************************//**
 * \file   EditorCamera.h
 * \brief  �G�f�B�^�[�g�p���̃J����
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ObjectListWindow;
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

