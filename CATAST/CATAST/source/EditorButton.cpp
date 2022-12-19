

void EditorButton::Init()
{
	_position = { 100.0f,100.0f,0.0f };
	auto aabb = std::make_unique<AABB2DComponent>();
	aabb->SetMovable(false);
	AddComponent(std::move(aabb));
	GetComponent<AABB2DComponent>()->SetSizeX(static_cast<float>(_sizeX));
	GetComponent<AABB2DComponent>()->SetSizeY(_sizeY);
}

void EditorButton::Update(InputManager& input)
{
	auto mousePositon = input.GetMouseXY();
	Vector2 mousePositonVec2{ static_cast<double>(mousePositon.first),static_cast<double>(mousePositon.second) };
	if (Within(GetComponent<AABB2DComponent>()->GetAABB(), mousePositonVec2)) {
		_state = State::MouseOver;
	}
	else {
		_state = State::Idle;
	}
	if (input.GetMouseLeft(InputState::Pressed)&&_state== State::MouseOver) {
		_state = State::Clicked;
		_activateFunction();
	}
}

void EditorButton::Render()
{
	auto color = GetColor(200, 200, 200);
	if (_state == State::MouseOver) {
		color = GetColor(100, 0, 0);
	}
	else if (_state == State::Clicked) {
		color = GetColor(20, 20, 20);
}

	DrawBox(static_cast<int>(_position.x)
		, static_cast<int>(_position.y)
		, static_cast<int>(_position.x + _sizeX)
		, static_cast<int>(_position.y + _sizeY)
		, color, true);


	DrawString(_position.x,_position.y, _text.c_str(),GetColor(0,0,0));
}

void EditorButton::Debug()
{
}

void EditorButton::SetText(std::string text)
{
	_text = text;
	_sizeX = _text.size() * (GetFontSize() / 2);
	_sizeY = GetFontSize();
}
