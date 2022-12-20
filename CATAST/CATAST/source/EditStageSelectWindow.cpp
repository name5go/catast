/*****************************************************************//**
 * \file   EditStageSelectWindow.cpp
 * \brief  編集するステージ番号を選択するウィンドウ
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

EditStageSelectWindow::EditStageSelectWindow(ObjectListWindow& list) :_list{ list }
{
	_name = "editor";
	_sizeX = GetFontSize() * 2;
	_sizeY = GetFontSize();
}

void EditStageSelectWindow::Update(InputManager& input)
{
	if (!_visible) {
		return;
	}
	if (input.GetMouseLeft(InputState::Pressed)) {
		auto mousePosition = input.GetMouseXY();
		int x = std::ceil((mousePosition.first - _position.x) / _sizeX);
		int y = std::floor((mousePosition.second - _position.y) / _sizeY);
		if (0<= y * 10 + x && y * 10 + x <= 100) {
			_list.SetSelectStage(y * 10 + x);
		}
	}
}

void EditStageSelectWindow::Render()
{
	if (!_visible) {
		return;
	}

	auto color1 = GetColor(255, 255, 255);
	auto color2 = GetColor(255, 255, 0);
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			int number = y * 10 + (x + 1);
			//選択したステージを黄色で表示
			auto color{ color1 };
			auto nume = _list.GetSelectStage();
			if (_list.GetSelectStage() == number) {
				color = color2;
			}

			DrawBox(static_cast<int>(_position.x) + _sizeX * x
				, static_cast<int>(_position.y) + _sizeY * y
				, static_cast<int>(_position.x) + _sizeX * x + _sizeX - 1
				, static_cast<int>(_position.y) + _sizeY * y + _sizeY - 1,
				color, true);
			DrawString(static_cast<int>(_position.x) + _sizeX * x
				, static_cast<int>(_position.y) + _sizeY * y
				, std::to_string(number).c_str()
				, GetColor(0.0f, 0.0f, 0.0f));
		}
	}
}

void EditStageSelectWindow::Debug()
{
}

bool EditStageSelectWindow::MessageEvent(ObjectBase* messenger, std::string message)
{
	if (message == "stageSelectOn") {
		_visible = true;
	}
	if (message == "stageSelectOff") {
		_visible = false;
	}
	return false;
}
