/*****************************************************************//**
 * \file   LevelBase.h
 * \brief  
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class LevelBase :
    public ObjectBase
{
public:
  void Init()override;
  void Update(InputManager&)override;
  void Render()override;
private:

};

