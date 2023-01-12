/*****************************************************************//**
 * \file   MV1Component.cpp
 * \brief  MV1のトランスフォーム更新、描画、アニメーションフレームの進行機能
 *
 * \author 土居将太郎
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
	, _animSpeed{ 1.0f }
{
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
	auto preTime = _playTime;
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
	_attahIndex = index;
	_attahIndex = MV1AttachAnim(_modelHandle, _attahIndex, -1, false);
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
	for (auto&& func : _animFunction[_attahIndex]) {
		if (func.first > preTime && func.first <= nowTime) {
			func.second;
		}
	}
}
