/*****************************************************************//**
 * \file   Camera.h
 * \brief  �J��������
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/

#pragma once


class Camera :
    public ObjectBase
{
public:
  void Init()override;
  void Update(InputManager&)override;
  void Render()override;
private:

};

