/*****************************************************************//**
 * \file   TestPlayer.h
 * \brief  �v���C���[�N���X�̉��u��
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/

#pragma once
#include "appframe.h"
class Player :
    public ObjectBase
{
public:
  void Init()override;
  void Update(InputManager&)override;
  void Render()override;
private:

};

