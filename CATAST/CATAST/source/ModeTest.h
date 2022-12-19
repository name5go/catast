/*****************************************************************//**
 * \file   ModeTest.h
 * \brief  ���[�h�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once


class ModeTest : public ModeBase
{
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Update(InputManager& input)override;
	bool Render()override;
	bool Debug()override;
}; 
