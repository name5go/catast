/*****************************************************************//**
 * \file   EditorCamera.cpp
 * \brief   エディター使用時のカメラ
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

EditorCamera::EditorCamera(ObjectListWindow& list):_list{list}, _light{0}
{
	_name = "editor";
}

EditorCamera::~EditorCamera()
{
	DeleteLightHandle(_light);
}

void EditorCamera::Init()
{
	ObjectBase::Init();
	_position = { 0.0f,50.0f,-150.0f };

	_light=CreateDirLightHandle(_rotation);
}

void EditorCamera::Update(InputManager& input)
{
	VECTOR forward{ VTransform({0.0f,0.0f,1.0f},_rotationMatrix) };
	VECTOR right{ VTransform({-1.0f,0.0f,0.0f},_rotationMatrix) };
	VECTOR up{ VTransform({0.0f,1.0f,0.0f},_rotationMatrix) };
	if (input.GetMouseRight(InputState::Hold)) {
		auto delta = input.GetMouseDeltaXY();
		_rotation = VAdd(_rotation, { static_cast<float>(delta.second * 0.01f),static_cast<float>(delta.first * 0.01f),0.0f });

		if (input.GetKeyW(InputState::Hold)) {
			_position = VAdd(_position, VScale(forward, 1.0f));
		}
		else if (input.GetKeyS(InputState::Hold)) {
			_position = VAdd(_position, VScale(forward, -1.0f));
		}
		if (input.GetKeyD(InputState::Hold)) {
			_position = VAdd(_position, VScale(right, -1.0f));
		}
		else if (input.GetKeyA(InputState::Hold)) {
			_position = VAdd(_position, VScale(right, 1.0f));
		}
	}
	else if (input.GetMouseMiddle(InputState::Hold)) {
		auto delta = input.GetMouseDeltaXY();
		_position = VAdd(_position, VScale(up, delta.second * 0.2f));
		_position = VAdd(_position, VScale(right, delta.first * 0.2f));
	}
	else if (input.GetMouseWheel() != 0) {
		_position = VAdd(_position, VScale(forward, input.GetMouseWheel()));
	}


	ObjectBase::Update(input);

	SetCameraPositionAndTargetAndUpVec(_position, VAdd(forward, _position), up);


	if (input.GetMouseLeft(InputState::Pressed)) {
		VECTOR screenPosStart{ static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()),0.0f };
		VECTOR screenPosEnd{ static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()),1.0f };
		VECTOR worldPosStart{ ConvScreenPosToWorldPos(screenPosStart) };
		VECTOR worldPosEnd{ ConvScreenPosToWorldPos(screenPosEnd) };

		for (auto&& object : _mode->GetObjectServer()->GetObjects()) {
			auto mv1Ptr=object->GetComponent<MV1Component>();
			if (mv1Ptr == nullptr) {
				continue;
			}
			auto handle = mv1Ptr->GetModelHandle();
			MV1RefreshCollInfo(handle, -1);
			auto result= MV1CollCheck_Line(handle, -1, worldPosStart, worldPosEnd);
			if (result.HitFlag) {
				_list.SetSelectID(object->GetID());
				break;
			}
		}
	}

	SetLightDirectionHandle(_light, forward);
}

void EditorCamera::Render()
{
	ObjectBase::Render();

}

void EditorCamera::Debug()
{
	ObjectBase::Debug();

	//std::stringstream ss;
	//ss << _rotation.x << "," << _rotation.y << "," << _rotation.z << "\n";
	//
	//DrawString(0.0f, 300.0f, ss.str().c_str(), GetColor(255, 255, 255));
}
