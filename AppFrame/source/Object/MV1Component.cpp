/*****************************************************************//**
 * \file   MV1Component.cpp
 * \brief  MV1�̃g�����X�t�H�[���X�V�A�`��A�A�j���[�V�����t���[���̐i�s�@�\
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#include "MV1Component.h"
#include "ObjectBase.h"
#include "../Mode/ModeBase.h"
#include <sstream>

MV1Component::MV1Component(int modelHandle)
	:_modelHandle{ modelHandle }
	, _attahIndex{ -1 }
	, _playTime{ 0.0f }
	, _totalTime{ 0.0f }
	, _animSpeed{ 60.0f }
	, _animIndex{-1}
{
	int animNumber = MV1GetAnimNum(_modelHandle);
	_animFunction.clear();
	_animFunction.resize(animNumber);
}

MV1Component::~MV1Component()
{
	MV1DeleteModel(_modelHandle);
}

bool MV1Component::Init()
{
	MV1SetScale(_modelHandle, _parent->GetScale());
	MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
	MV1SetPosition(_modelHandle, _parent->GetPosition());
	return true;
}

void MV1Component::Update()
{
	if (_attahIndex == -1) {
		return;
	}
	float preTime = _playTime;
	_playTime += _parent->GetMode()->GetStepTime() * 0.001f * _animSpeed;
	CheckAnimFunction(preTime, _playTime);
	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}
}

void MV1Component::Render()
{
	MV1SetScale(_modelHandle, _parent->GetScale());
	MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
	MV1SetPosition(_modelHandle, _parent->GetPosition());
	MV1SetAttachAnimTime(_modelHandle, _attahIndex, _playTime);
	MV1DrawModel(_modelHandle);

}
void MV1Component::Debug()
{

}

void MV1Component::SetModelHandle(int modelHandle)
{
	_modelHandle = modelHandle;
	int animNumber = MV1GetAnimNum(modelHandle);
	_animFunction.clear();
	_animFunction.resize(animNumber);
}

void MV1Component::SetAnimation(int index)
{
	MV1DetachAnim(_modelHandle, _attahIndex);
	_animIndex = index;
	_attahIndex = MV1AttachAnim(_modelHandle, _animIndex, -1, true);
	_totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _attahIndex);
	_playTime = 0.0f;
}

void MV1Component::AddAnimFunction(int animIndex, float activateTime, std::function<void(void)> function)
{
	if (_animFunction.size() - 1 < animIndex) {
		return;
	}
	_animFunction[animIndex].push_back({ activateTime,function });

	typedef std::pair<float, std::function<void(void)>> AnimFuncType;
	auto sortAnimFunc = [](AnimFuncType lhs, AnimFuncType rhs) {return lhs.first < rhs.first; };

	std::sort(_animFunction[animIndex].begin(), _animFunction[animIndex].end(), sortAnimFunc);
}

void MV1Component::CheckAnimFunction(float preTime, float nowTime)
{
	for (auto&& func : _animFunction[_animIndex]) {
		if (func.first > preTime && func.first <= nowTime) {
			func.second();
		}
	}
}
