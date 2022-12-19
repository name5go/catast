/*****************************************************************//**
 * \file   EditorUICreater.h
 * \brief  �X�e�[�W�G�f�B�^�p��UI��z�u����N���X
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ObjectListWindow;

class EditorUICreater
{
public:
	void CreateUI(ObjectServer&);
	void DeleteUI(ObjectServer&);
private:
	void AddObjectUI(ObjectServer&, ObjectListWindow&);
	void TransformUI(ObjectServer&, ObjectListWindow&);
	void FileUI(ObjectServer& objectServer, ObjectListWindow& list);
	void End(ObjectServer& objectServer, ObjectListWindow& list);
};

