/*****************************************************************//**
 * \file   ModeConfig.h
 * \brief  �R���t�B�O
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/
#pragma once

class ModeConfig :
    public ModeBase
{
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Update(InputManager& input)override;
	bool Render()override;
	bool Debug()override;
};

