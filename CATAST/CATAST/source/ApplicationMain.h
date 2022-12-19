#include "appframe.h"
class ApplicationMain : public ApplicationBase
{
public:
	bool Initialize(HINSTANCE hInstance)override;
	bool Terminate()override;
	bool Input()override;
	bool Update()override;
	bool Render()override;

	bool AppWindowed()override { return true; }
	int DispSizeW()override { return 1920; }
	int DispSizeH()override { return 1080; }

private:
}; 
