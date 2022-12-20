/*****************************************************************//**
 * \file   XYZLine.h
 * \brief  XYZ軸を表示するオブジェクト
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

XYZLine::XYZLine()
{
	_name = "editor";
}

void XYZLine::Render()
{
	DrawLine3D({ 0,0,0 }, { 100,0,0 }, GetColor(255, 0, 0));
	DrawLine3D({ 0,0,0 }, { 0,100,0 }, GetColor(0, 255, 0));
	DrawLine3D({ 0,0,0 }, { 0,0,100 }, GetColor(0, 0, 255));
}
