/*****************************************************************//**
 * \file   InputManager.cpp
 * \brief  入力取得クラス
 *
 * \author 土居将太郎
 * \date   October 2022
 *********************************************************************/
#include "InputManager.h"
#include <sstream>
//コントローラー数の設定
namespace {
	constexpr int controllerNumber = 1;
}
InputManager::InputManager()
	:_mouse{ 0 },
	_oldMouse{ 0 }
{
	Init();
}

InputManager::~InputManager() {

}

void InputManager::Init() {

	GetMousePoint(&_mouseX, &_mouseY);
	_mouse = GetMouseInput();

	_keys.resize(controllerNumber);
	_oldKeys.resize(controllerNumber);
	for (int i = 0; i < _keys.size(); ++i) {
		_keys[i] = 0;
		_oldKeys[i] = 0;
	}
}

void InputManager::Input() {
	_oldMouse = _mouse;

	for (int i = 0; i < _keys.size(); ++i) {
		_oldKeys[i] = _keys[i];
	}
	for (int i = 0; i < _keys.size(); ++i) {
		_keys[0] = GetJoypadInputState(_controllerList[i]);
	}

	GetMousePoint(&_mouseX, &_mouseY);
	_mouse = GetMouseInput();

}
void InputManager::Debug() {
	std::stringstream ss;
	ss << _keys[0];
	DrawString(0, 0, ss.str().c_str(), GetColor(255, 255, 255));
}

bool InputManager::GetMouseButton(int key, InputState state) {
	int pressed{ 0 };
	int released{ 0 };
	switch (state)
	{
	case InputState::Hold:
		return _mouse & key;
	case InputState::Pressed:
		pressed = (_oldMouse ^ _mouse) & _mouse;
		return pressed & key;
	case InputState::Released:
		released = (_oldMouse ^ _mouse) & _oldMouse;
		return released & key;
	default:
		return false;
	}
}

bool InputManager::GetKeyButton(int key, InputState state, int controllerNumber) {
	if (controllerNumber > _keys.size()) {
		return false;
	}
	int pressed{ 0 };
	int released{ 0 };
	int currentkey = _keys[controllerNumber];
	int oldKey = _oldKeys[controllerNumber];
	switch (state)
	{
	case InputState::Hold:
		return currentkey & key;
	case InputState::Pressed:
		pressed = (oldKey ^ currentkey) & currentkey;
		return pressed & key;
	case InputState::Released:
		released = (oldKey ^ currentkey) & oldKey;
		return released & key;
	default:
		return false;
	}
}
