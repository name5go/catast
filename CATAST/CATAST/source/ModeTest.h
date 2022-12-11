/*****************************************************************//**
 * \file   ModeTest.h
 * \brief  モードの実装例です。ゲーム中では使用しない。
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "appframe.h"

class ModeTest : public ModeBase
{
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Update(InputManager& input)override;
	bool Render()override;
	bool Debug()override;
}; 
