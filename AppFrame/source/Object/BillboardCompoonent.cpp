#include "BillboardCompoonent.h"
#include "ObjectBase.h"
namespace AppFrame {

	BillboardCompoonent::BillboardCompoonent(int imageHandle)
		:_imageHandle{ imageHandle }
	{
		int sizeX,sizeY;
		GetGraphSize(imageHandle, &sizeX, &sizeY);
		_sizeX = static_cast<float>(sizeX);
	}

	BillboardCompoonent::~BillboardCompoonent()
	{
	}

	void BillboardCompoonent::Update()
	{
	}

	void BillboardCompoonent::Render()
	{
		DrawBillboard3D(_parent->GetRotation(),0.5f,0.5f, _sizeX, _parent->GetRotation().x,_imageHandle,true);
	}
	void BillboardCompoonent::SetImageHandle(int imageHandle)
	{
		_imageHandle = imageHandle;
		int sizeX, sizeY;
		GetGraphSize(imageHandle, &sizeX, &sizeY);
		_sizeX = static_cast<float>(sizeX);
	}
}
