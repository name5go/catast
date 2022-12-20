/*****************************************************************//**
 * \file   EditorSelectMarker.cpp
 * \brief   選択した物体を示すマーカー
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

EditorSelectMarker::EditorSelectMarker(ObjectListWindow& list)
	:_list{list}
{
	_name = "editor";
	_layer = 2;
}

void EditorSelectMarker::Update(InputManager& input)
{
	auto objectPtr=_mode->GetObjectServer()->Get(_list.GetSelectID());
	if (objectPtr == nullptr) {
		_visible = false;
		return;
	}
	_visible = true;
	_position = objectPtr->GetPosition();
}

void EditorSelectMarker::Render()
{
	ObjectBase::Render();
	if (!_visible) {
		return;
	}
	SetUseZBuffer3D(false);
	SetUseLighting(false);
	DrawLine3D(_position,VAdd(_position,{10,0,0}),GetColor(255,0,0));
	DrawLine3D(_position, VAdd(_position, { 0,10,0 }), GetColor(0, 255, 0));
	DrawLine3D(_position, VAdd(_position, { 0,0,10 }), GetColor(0, 0, 255));
	DrawSphere3D(_position,1.0f,4,GetColor(255,255,0), GetColor(0, 0,0 ), true);
	SetUseZBuffer3D(true);
	SetUseLighting(true);
}
