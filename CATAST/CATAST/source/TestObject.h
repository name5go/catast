/*****************************************************************//**
 * \file   TestObject.h
 * \brief  �I�u�W�F�N�g�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "PrecompiledHeader.h"
#include "appframe.h"

class TestObject : public ObjectBase
{
public:
    void Init()override;
    void Update(InputManager&)override;
    void Render()override;
private:

};

