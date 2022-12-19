/*****************************************************************//**
 * \file   EditorUICreater.h
 * \brief  ステージエディタ用のUIを配置するクラス
 * 
 * \author 土居将太郎
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

