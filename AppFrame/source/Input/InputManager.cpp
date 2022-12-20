/*****************************************************************//**
 * \file   InputManager.cpp
 * \brief  ���͎擾�N���X
 *
 * \author �y�������Y
 * \date   October 2022
 *********************************************************************/
#include "InputManager.h"
#include <sstream>
 //�R���g���[���[���̐ݒ�
namespace {
	constexpr int controllerNumber = 1;
}
InputManager::InputManager()
	:_mouse{ 0 }
	, _oldMouse{ 0 }
	, _mouseOldX{ 0 }
	, _mouseOldY{ 0 }
	, _mouseWheel{ 0 }
{
	Init();
}

InputManager::~InputManager() {

}

void InputManager::Init() {
	GetHitKeyStateAll(_keyboardKeys);
	GetMousePoint(&_mouseX, &_mouseY);
	_mouse = GetMouseInput();

	_padKeys.resize(controllerNumber);
	_oldPadKeys.resize(controllerNumber);
	_padX.resize(controllerNumber);
	_padY.resize(controllerNumber);
	for (int i = 0; i < _padKeys.size(); ++i) {
		_padKeys[i] = 0;
		_oldPadKeys[i] = 0;
	}
}

void InputManager::Input() {
	//�L�[�{�[�h���͍X�V
	for (int i = 0; i < 256; ++i) {
		_oldKeyboardKeys[i] = _keyboardKeys[i];
	}
	GetHitKeyStateAll(_keyboardKeys);
	//�}�E�X���͍X�V
	_oldMouse = _mouse;
	_mouseOldX = _mouseX;
	_mouseOldY = _mouseY;
	GetMousePoint(&_mouseX, &_mouseY);
	_mouse = GetMouseInput();
	_mouseWheel = GetMouseWheelRotVol();

	//�p�b�h���͍X�V
	for (int i = 0; i < _padKeys.size(); ++i) {
		_oldPadKeys[i] = _padKeys[i];
	}
	for (int i = 0; i < _padKeys.size(); ++i) {
		_padKeys[0] = GetJoypadInputState(_controllerList[i]);
		GetJoypadAnalogInput(&_padX[i], &_padY[i], _controllerList[i]);
	}
	//xInput�X�V
	GetJoypadXInputState(DX_INPUT_PAD1, &xInput);
}

void InputManager::Debug() {
	std::stringstream ss;
	ss << _padKeys[0] << "\n";
	DrawString(0, 100, ss.str().c_str(), GetColor(255, 255, 255));
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

bool InputManager::GetKeyButton(int key, InputState state)
{
	bool currentkey{ false };
	if (_keyboardKeys[key] == 1) {
		currentkey = true;
	}
	bool oldKey{ false };
	if (_oldKeyboardKeys[key] == 1) {
		oldKey = true;
	}
	switch (state)
	{
	case InputState::Hold:
		return currentkey;
	case InputState::Pressed:
		return (oldKey ^ currentkey) && currentkey;
	case InputState::Released:
		return (oldKey ^ currentkey) && oldKey;
	default:
		return false;
	}
}

bool InputManager::GetPadButton(int key, InputState state, int controllerNumber) {
	if (controllerNumber > _padKeys.size()) {
		return false;
	}
	int pressed{ 0 };
	int released{ 0 };
	int currentkey = _padKeys[controllerNumber];
	int oldKey = _oldPadKeys[controllerNumber];
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
