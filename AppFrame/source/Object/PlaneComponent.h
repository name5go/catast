#pragma once
#include "ComponentBase.h"
namespace AppFrame {

	class PlaneComponent :public ComponentBase
	{
	public:
		PlaneComponent(int imageHandle);
		~PlaneComponent();
		bool Init()override;
		void Update()override;
		void Render()override;
		void SetImageHandle(int imageHandle);
		int GetImageHandle() { return _imageHandle; }

	private:
		void SetImageSize();

		int _imageHandle;
		float _sizeX, _sizeY;
		COLOR_U8 _diffuseColor;
		COLOR_U8 _specularColor;
	};

}