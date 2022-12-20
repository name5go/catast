/*****************************************************************//**
 * \file   DummyBounce.h
 * \brief  仮反射ギミック
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyBounce : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

