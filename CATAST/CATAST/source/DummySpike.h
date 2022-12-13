#pragma once
#include "appframe.h"
class DummySpike :
    public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

