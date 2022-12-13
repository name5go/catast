#include "EditorButton.h"
#include "ObjectListWindow.h"

EditorButton::EditorButton(ObjectListWindow& list)
	:_text{ "ƒ{ƒ^ƒ“" }
	, _state{ State::Idle }
	, _sizeX{ 48 }
	, _sizeY{ 16 }
	, _list{ list }
	, _activateFunction{ [](ObjectListWindow*) {} }
	, _nonactivateFunction{ [](ObjectListWindow*) {} }
	, _toggle{ false }
{
	_name = "editor";
	_layer = 2;
	_position = { 100.0f,100.0f,0.0f };
}

void EditorButton::Init()
{
	auto aabb = std::make_unique<AABB2DComponent>();
	aabb->SetMovable(false);
	aabb->SetSizeX(static_cast<float>(_sizeX));
	aabb->SetSizeY(static_cast<float>(_sizeY));
	AddComponent(std::move(aabb));
}

void EditorButton::Update(InputManager& input)
{
	if (!_visible) {
		return;
	}
	auto mousePositon = input.GetMouseXY();
	Vector2 mousePositonVec2{ static_cast<double>(mousePositon.first),static_cast<double>(mousePositon.second) };
	if (!_toggle) {
		if (Within(GetComponent<AABB2DComponent>()->GetAABB(), mousePositonVec2)) {
			_state = State::MouseOver;
		}
		else {
			_state = State::Idle;
		}
		if (input.GetMouseLeft(InputState::Pressed) && _state == State::MouseOver) {
			_state = State::Clicked;
			_activateFunction(&_list);
		}
	}
	else {
		if (input.GetMouseLeft(InputState::Pressed) && Within(GetComponent<AABB2DComponent>()->GetAABB(), mousePositonVec2)) {
			if (_state == State::Clicked) {
				_state = State::Idle;
				_nonactivateFunction(&_list);
			}
			else {
				_state = State::Clicked;
				_activateFunction(&_list);
			}
		}
	}
}

void EditorButton::Render()
{
	if (!_visible) {
		return;
	}
	auto color = GetColor(200, 200, 200);
	auto textColor=GetColor(0, 0, 0);
	if (_state == State::MouseOver) {
		color = GetColor(130, 130, 150);
	}
	else if (_state == State::Clicked) {
		color = GetColor(20, 20, 20);
		textColor = GetColor(255, 255, 255);
	}
	//‰º’n
	DrawBox(static_cast<int>(_position.x)
		, static_cast<int>(_position.y)
		, static_cast<int>(_position.x + _sizeX)
		, static_cast<int>(_position.y + _sizeY)
		, GetColor(200, 200, 200), true);
	DrawBox(static_cast<int>(_position.x)+1
		, static_cast<int>(_position.y)+1
		, static_cast<int>(_position.x + _sizeX)-1
		, static_cast<int>(_position.y + _sizeY)-1
		, color, true);

	DrawString(_position.x, _position.y, _text.c_str(), textColor);
}

void EditorButton::Debug()
{
}

void EditorButton::SetText(std::string text)
{
	_text = text;
	_sizeX = (_text.size() + 1) * (GetFontSize() / 2);
	_sizeY = GetFontSize();
}

bool EditorButton::MessageEvent(ObjectBase* messenger, std::string message)
{
	if (message==_unPushedMessage) {
		if (_state == State::Clicked) {
			_state = State::Idle;
			_nonactivateFunction(&_list);
		}
	}
	if (message == _visibleMessage) {
		_visible = true;
	}
	if (message == _invisibleMessage) {
		_visible = false;
	}
	return false;
}
