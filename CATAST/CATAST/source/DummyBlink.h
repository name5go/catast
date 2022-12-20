/*****************************************************************//**
 * \file   DummyBlink.h
 * \brief  仮透明ギミック
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyBlink :
    public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

