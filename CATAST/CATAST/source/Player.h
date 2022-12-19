#pragma once
#include "PrecompiledHeader.h"
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

