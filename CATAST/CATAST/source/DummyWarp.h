#pragma once
#include "appframe.h"
class DummyWarp : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

