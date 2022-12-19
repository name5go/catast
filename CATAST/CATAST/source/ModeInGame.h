/*****************************************************************//**
 * \file   ModeInGame.h
 * \brief  �C���Q�[�������ł�
 * 
 * \author �߂���
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

