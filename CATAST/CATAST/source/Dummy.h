/*****************************************************************//**
 * \file   Dummy.h
 * \brief  仮ターゲット
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class Dummy : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
	bool MessageEvent(ObjectBase* obj, std::string msg)override;
private:
};