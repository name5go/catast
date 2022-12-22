#include "PrecompiledHeader.h"


CameraComponent::CameraComponent(float cameraDistance)
{
	_cameraPosition = { 0.0f,50.0f,-150.0f };
	_cameraTarget = { 0.0f,50.0f,0.0f };
	_cameraDistance = { 0.0f,50.0f,-150.0f };
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	_cameraPosition = VAdd(_cameraDistance, _parent->GetPosition());
	//SetCameraPositionAndTargetAndUpVec(VAdd(_cameraDistance, _parent->GetPosition()), _parent->GetPosition(), _cameraTarget);
	SetCameraPositionAndTarget_UpVecY(_cameraPosition, _parent->GetPosition());
}

void CameraComponent::Render()
{
}

void CameraComponent::Debug()
{
}
