/*****************************************************************//**
 * \file   MV1Component.cpp
 * \brief  MV1�̃g�����X�t�H�[���X�V�A�`��A�A�j���[�V�����t���[���̐i�s�@�\
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#include "MV1Component.h"
#include "ObjectBase.h"
#include <sstream>

MV1Component::MV1Component(int modelHandle)
	:_modelHandle{ modelHandle }
	, _attahIndex{ -1 }
	, _playTime{ 0 }
	, _totalTime{ 0 }
{
}

MV1Component::~MV1Component()
{
	MV1DeleteModel(_modelHandle);
}

void MV1Component::Update()
{
	if (_attahIndex == -1) {
		return;
	}
	_playTime += 0.5f;
	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}
}

void MV1Component::Render()
{
	MV1SetScale(_modelHandle, _parent->GetScale());
	MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
	MV1SetPosition(_modelHandle, _parent->GetPosition());
	MV1DrawModel(_modelHandle);
	MV1SetAttachAnimTime(_modelHandle, _attahIndex, _playTime);
}
void MV1Component::Debug()
{
}
void MV1Component::SetAnimation(int index)
{
	MV1DetachAnim(_modelHandle,_attahIndex);
	_attahIndex = index;
	_attahIndex = MV1AttachAnim(_modelHandle, _attahIndex, -1, false);
	_totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _attahIndex);
	_playTime = 0.0f;
}
