/*****************************************************************//**
 * \file   EditorTextBox.cpp
 * \brief  数値を入力するボックス
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/

EditorTextBox::EditorTextBox(ObjectListWindow& list)
	:_list{ list }
	, _sizeX{ 50 }
	, _sizeY{ 20 }
{
}

EditorTextBox::~EditorTextBox()
{
}

void EditorTextBox::Init()
{
	auto aabb=std::make_unique<AABB2DComponent>();
	aabb->SetSizeX(_sizeX);
	aabb->SetSizeY(_sizeY);
	AddComponent(std::move(aabb));
}

void EditorTextBox::Update(InputManager& input)
{
	if (input.GetMouseLeft(InputState::Pressed)) {
		Vector2 mouseXY = { static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()) };
		if (Within(GetComponent<AABB2DComponent>()->GetAABB(), mouseXY)) {

		}
	}
}

void EditorTextBox::Render()
{
	DrawBox(_position.x, _position.y, _position.x + 50, _position.y + 20, GetColor(255, 255, 255), true);
	DrawBox(_position.x, _position.y, _position.x + 50, _position.y + 20, GetColor(0, 0, 0), false);
	auto objPtr = _mode->GetObjectServer()->Get(_list.GetSelectID());
	if (objPtr != nullptr) {
		std::string x = std::to_string(static_cast<int>(objPtr->GetPosition().x));
		DrawString(_position.x, _position.y, x.c_str(), GetColor(0, 0, 0));
	}
}

void EditorTextBox::Debug()
{
}
