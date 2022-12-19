/*****************************************************************//**
 * \file   ObjectListWindow.h
 * \brief  配置しているオブジェクトのリストを表示するUI
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "ObjectListWindow.h"
#include "Dummy.h"
#include "DummyBlink.h"
#include "DummyBounce.h"
#include "DummySpike.h"
#include "DummyWarp.h"
#include <sstream>

ObjectListWindow::ObjectListWindow()
	:_scroll{ 0 }, _selectID{ -1 }, _sizeX{ 300 }, _sizeY{ 400 }, _selectStage{ 1 },_copy{nullptr}
{
	_name = "editor";
}

void ObjectListWindow::Init()
{
	int x, y;
	GetWindowSize(&x, &y);
	_position = { static_cast<float>(x - _sizeX),16.0f,0.0f };
}

void ObjectListWindow::Update(InputManager& input)
{
	_gimmickNumber=0;
	for (auto&& object : _mode->GetObjectServer()->GetObjects()) {
		if (object->GetName() != "gimmick") {
			continue;
		}
		++_gimmickNumber;
	}

	std::vector<int> IDarray;
	for (auto&& object : _mode->GetObjectServer()->GetObjects()) {
		std::stringstream ss2;
		if (object->GetName() != "gimmick") {
			continue;
		}
		IDarray.push_back(object->GetID());
	}
	if (input.GetMouseLeft(InputState::Pressed)) {
		auto mousePosition = input.GetMouseXY();
		if (mousePosition.first >= _position.x && mousePosition.first <= _position.x + _sizeX-30) {
			int lineIndex = std::floor((mousePosition.second - _position.y) / GetFontSize());
			if (_mode->GetObjectServer()->GetObjects().size() > lineIndex) {
				if (lineIndex < IDarray.size()) {
					_selectID = IDarray[lineIndex] + _scroll;;
				}
			}
		}
	}

	if (input.GetKeyDelete(InputState::Pressed)) {
		auto delPtr=_mode->GetObjectServer()->Get(_selectID);
		if (delPtr!=nullptr) {
			delPtr->Dead();
		}
	}

	if (input.GetKeyControlLeft(InputState::Hold)&& input.GetKeyC(InputState::Pressed)) {
		auto copyPtr = _mode->GetObjectServer()->Get(_selectID);
		if (copyPtr->CheckType<Dummy>()) {
			Copy<Dummy>(copyPtr);
		}
		if (copyPtr->CheckType<DummyBlink>()) {
			Copy<DummyBlink>(copyPtr);
		}
		if (copyPtr->CheckType<DummyBounce>()) {
			Copy<DummyBounce>(copyPtr);
		}
		if (copyPtr->CheckType<DummySpike>()) {
			Copy<DummySpike>(copyPtr);
		}
		if (copyPtr->CheckType<DummyWarp>()) {
			Copy<DummyWarp>(copyPtr);
		}
	}
	if (input.GetKeyControlLeft(InputState::Hold) && input.GetKeyV(InputState::Pressed)) {
		if (_copy != nullptr) {
			if (_copy->CheckType<Dummy>()) {
				Paste<Dummy>();
			}
			if (_copy->CheckType<DummyBlink>()) {
				Paste<DummyBlink>();
			}
			if (_copy->CheckType<DummyBounce>()) {
				Paste<DummyBounce>();
			}
			if (_copy->CheckType<DummySpike>()) {
				Paste<DummySpike>();
			}
			if (_copy->CheckType<DummyWarp>()) {
				Paste<DummyWarp>();
			}
		}
	}
}

void ObjectListWindow::Render()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(_position.x, _position.y, _position.x + _sizeX, _position.y + _sizeY, GetColor(50, 50, 50), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	std::stringstream ss;
	ss << "ステージ：" << _selectStage;
	DrawString(_position.x, _position.y-16.0f, ss.str().c_str(), GetColor(255, 255, 255));

	SetDrawArea(_position.x, _position.y, _position.x + _sizeX, _position.y + _sizeY);

	auto&& objects = _mode->GetObjectServer()->GetObjects();

	int scroll{ 0 };

	if (_gimmickNumber > 24){

		if (_gimmickNumber - 24 >_scroll) {
			scroll = _scroll;
		}
		else {
			scroll = _gimmickNumber - 25;
		}
	}

	int count{ 0 };
	for (auto&& object : objects) {
		auto color = GetColor(255, 255, 255);
		std::stringstream ss2;
		if (object->GetName() != "gimmick") {
			continue;
		}
		ss2 << count<<":";
		if (object->GetID() == _selectID) {
			color = GetColor(255, 0, 0);
		}
		if (object->CheckType<Dummy>()) {
			ss2 << "仮ターゲット"<< object->GetID();
		}else if (object->CheckType<DummyBlink>()) {
			ss2 << "仮透明ギミック" << object->GetID();
		}else if (object->CheckType<DummyBounce>()) {
			ss2 << "仮反射ギミック" << object->GetID();
		}else if (object->CheckType<DummySpike>()) {
			ss2 << "仮一方行ターゲット" << object->GetID();
		}else if (object->CheckType<DummyWarp>()) {
		ss2 << "仮ワープギミック" << object->GetID();
	}
		else {
			ss2 << typeid(*object).name();
		}
		DrawString(_position.x, _position.y + GetFontSize() * (count- scroll), ss2.str().c_str(), color);
		++count;
	}

	SetDrawArea(0, 0, 1920, 1080);

}

void ObjectListWindow::ScrollUp()
{
	--_scroll;
	if (_scroll < 0) {
		_scroll = 0;
	}
}

void ObjectListWindow::ScrollDown()
{
	++_scroll;
	if (_gimmickNumber > 24 && _scroll> _gimmickNumber - 25) {
		_scroll = _gimmickNumber - 25;
	}
}

template<typename T>
void ObjectListWindow::Copy(ObjectBase* copyPtr)
{
	auto dummy = std::make_unique<T>();
	dummy->SetPosition(copyPtr->GetPosition());
	dummy->SetRotation(copyPtr->GetRotation());
	dummy->SetScale(copyPtr->GetScale());
	_copy = std::move(dummy);
}

template<typename T>
void ObjectListWindow::Paste()
{
	auto dummy = std::make_unique<T>();
	dummy->SetPosition(_copy->GetPosition());
	dummy->SetRotation(_copy->GetRotation());
	dummy->SetScale(_copy->GetScale());
	_mode->GetObjectServer()->Add(std::move(dummy));
}