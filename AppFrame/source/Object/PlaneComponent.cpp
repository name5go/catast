#include "PlaneComponent.h"
#include "ObjectBase.h"
namespace AppFrame {

	PlaneComponent::PlaneComponent(int imageHandle)
		:_imageHandle{ imageHandle }
		, _diffuseColor{ GetColorU8(255,255,255,255) }
		,_specularColor{ GetColorU8(0,0,0,0) }
	{
	}

	PlaneComponent::~PlaneComponent()
	{
	}

	bool PlaneComponent::Init()
	{
		AppFrame::ComponentBase::Init();
		SetImageSize();
		return true;
	}

	void PlaneComponent::Update()
	{
	}

	void PlaneComponent::Render()
	{
		auto scale = _parent->GetScale();
		auto pos1=_parent->GetPosition();
		pos1.x -= _sizeX / 2* scale.x;
		pos1.z -= _sizeY / 2* scale.z;
		auto pos2 = pos1;
		pos2.x += _sizeX*scale.x;
		auto pos3 = pos1;
		pos3.z += _sizeY* scale.z;
		auto pos4 = pos1;
		pos4.x += _sizeX* scale.x;
		pos4.z += _sizeY* scale.z;

		VERTEX3D vertex[4] = {
			{ pos1, _parent->GetRotation(), _diffuseColor, _specularColor, 0, 1, 0, 0 },
			{ pos2, _parent->GetRotation(), _diffuseColor, _specularColor, 1, 1, 0, 0},
			{ pos3, _parent->GetRotation(), _diffuseColor, _specularColor, 0, 0, 0, 0 },
			{ pos4, _parent->GetRotation(), _diffuseColor, _specularColor, 1, 0, 0, 0 },
		};
		unsigned short indices[6] = { 0,1,2,1,3,2 };

		DrawPolygonIndexed3D(vertex,4, indices,2,_imageHandle,true);
	}

	void PlaneComponent::SetImageHandle(int imageHandle)
	{
		_imageHandle = imageHandle;
		SetImageSize();
	}

	void PlaneComponent::SetImageSize()
	{
		int sizeX, sizeY;
		GetGraphSize(_imageHandle, &sizeX, &sizeY);
		_sizeX = static_cast<float>(sizeX);
		_sizeY = static_cast<float>(sizeY);
	};
}
