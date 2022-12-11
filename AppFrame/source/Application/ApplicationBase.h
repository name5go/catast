#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

class ModeServer;
class InputManager;


	class ApplicationBase
	{
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		virtual bool Initialize(HINSTANCE hInstance);
		virtual bool Terminate();
		virtual bool Input();
		virtual bool Update();
		virtual bool Render();

		virtual bool AppWindowed() { return true; }
		virtual int DispSizeW() { return 640; }
		virtual int DispSizeH() { return 480; }

		static	ApplicationBase* GetInstance() { return _lpInstance; }

	protected:
		static	ApplicationBase* _lpInstance;

		std::unique_ptr<ModeServer> _modeServer;
		std::unique_ptr<InputManager> _inputManager;
	};