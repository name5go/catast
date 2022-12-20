/*****************************************************************//**
 * \file   DummyWarp.h
 * \brief  仮ワープギミック
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyWarp : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

