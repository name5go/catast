#pragma once
#include "appframe.h"
class DummyBlink :
    public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

