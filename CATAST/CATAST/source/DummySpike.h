/*****************************************************************//**
 * \file   DummySpike.h
 * \brief  仮一方向ギミック
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once

class DummySpike :
    public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

