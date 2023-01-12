/*****************************************************************//**
 * \file   ModeInGame.h
 * \brief  インゲーム部分です
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/

#pragma once


class ModeInGame :
    public ModeBase
{
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Update(InputManager& input)override;
	bool Render()override;
	bool Debug()override;
private:
};

