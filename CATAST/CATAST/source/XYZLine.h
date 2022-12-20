/*****************************************************************//**
 * \file   XYZLine.h
 * \brief  XYZ軸を表示するオブジェクト
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class XYZLine : public ObjectBase
{
public:
	XYZLine();
	void Render()override;
private:
};