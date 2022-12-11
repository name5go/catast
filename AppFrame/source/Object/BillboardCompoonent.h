#pragma once
#include "ComponentBase.h"
namespace AppFrame {
	class BillboardCompoonent : public ComponentBase
	{
	public:
		BillboardCompoonent(int imageHandle);
		~BillboardCompoonent();
		void Update()override;
		void Render()override;
		void SetImageHandle(int imageHandle);
		int GetImageHandle() { return _imageHandle; }
	private:
		int _imageHandle;
		float _sizeX;
	};
}
