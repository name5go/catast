/*****************************************************************//**
 * \file   MessageWindow.cpp
 * \brief  メッセージが表示されるウィンドウ
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
namespace {
	constexpr int sizeW = 1100;
	constexpr int sizeH = 200;
	constexpr float positionYRaito = 0.85f;//Y位置決定用、ウィンドウの縦サイズに対しての比率
	constexpr int iconPadding = 50;//キャラ画像周りの空白の大きさ
	constexpr float messageSpeed = 0.05f;//1文字フェードインするのに使用する時間sec
	constexpr int linesSpace = 40;//行間px
	constexpr int shadowOffset = 2;//文字影を右下へずらす量px
	constexpr int insertImageSize = 32;//文中に挿入する画像サイズXYpx
}

MessageWindow::MessageWindow()
	:_message{ "NoData" }
	, _nameText{ "NoData" }
	, _time{ 0 }
	, _drawingByte{ 0 }
	, _messageFinished{ false }
	, _lineMax{ 1 }
	, _fontSize{ 32 }
	, _wait{ 0 }
	, _drawingImage{ -1 }
{
	auto width = ApplicationBase::GetInstance()->DispSizeW();
	auto height = ApplicationBase::GetInstance()->DispSizeH();
	_position = { static_cast<float>(width / 2),static_cast<float>(height) * positionYRaito + iconPadding,0.0f };
	_screen = MakeScreen(ApplicationBase::GetInstance()->DispSizeW(), ApplicationBase::GetInstance()->DispSizeH(), true);
	_font = FontServer::LoadFont("res/Font/emoir-kakuB4S32.dft");
	_fontSize = GetFontSizeToHandle(_font);
	_cg = ImageServer::LoadGraph("res/UI/CharaIcon.png");
	_insetImageList.fill(-1);
	_insetImageList[0] = _cg;
	_color = GetColor(255, 255, 255);

	SetMassage("ダミーくん", "こんにちは@p0こんばんは@c1\nABCD123456789");
}

MessageWindow::~MessageWindow()
{
}

void MessageWindow::Init()
{
	_font = FontServer::LoadFont("res/Font/emoir-kakuB4S32.dft");
	_fontSize = GetFontSizeToHandle(_font);
	_color = GetColor(255, 255, 255);
	_messageFinished = false;
	_drawingByte = 0;
	_drawingPositionX = 0;
	_drawingLine = 0;
	_time = 0;
}

void MessageWindow::Update(InputManager& input)
{
	ObjectBase::Update(input);
	if (input.GetKeySPACE(InputState::Pressed)) {
		SetMassage("ダミーくん", "こん@p0 \nにち\nは@w1こ");
	}
	if (input.GetKeyZ(InputState::Pressed)) {
		SetMassage("ダミーくん", "本年も格別の@c2ご厚情@c1を賜り、\n心より感謝申しあげます。");
	}
	if (input.GetKeyC(InputState::Pressed)) {
		SetMassage("ダミーくん", "Eigo Ha Douse Kakanyaro\n13246789");
	}

}

void MessageWindow::Render()
{
	if (!_visible) {
		return;
	}

	if (_messageFinished) {
		DrawGraph(0, 0, _screen, true);
		return;
	}

	int size = 0;//1文字あたりのバイト数

	size = ShiftJISChecker::Check(_message[_drawingByte]);

	//sに描画する文字を入れる
	std::string s = "";
	for (int i = 0; i < size; i++) {
		s += _message[_drawingByte + i];
	}

	//\nなら改行して終わり
	if (s == "\n") {
		++_drawingLine;
		_drawingPositionX = 0;
		_time = messageSpeed;
		_drawingByte += size;
		DrawGraph(0, 0, _screen, true);
		return;
	}
	//@ならコマンド読み込み
	if (s == "@") {
		//2byte先まではコマンド内容
		s += _message[_drawingByte + 1];
		s += _message[_drawingByte + 2];
		if (s == "@c1") {
			_color = GetColor(255, 255, 255);
		}
		if (s == "@c2") {
			_color = GetColor(242, 133, 7);
		}
		if (s == "@s1") {
			_font = FontServer::LoadFont("res/Font/emoir-kakuB4S32.dft");
			_fontSize = GetFontSizeToHandle(_font);
		}
		if (s == "@s2") {
			_font = FontServer::LoadFont("res/Font/emoir-kakuB4S22.dft");
			_fontSize = GetFontSizeToHandle(_font);
		}
		if (s == "@w1") {
			_wait = 0.5f;
		}
		if (s == "@w2") {
			_wait = 1.0f;
		}
		if (s[1] == 'p') {
			std::string index(1, s[2]);
			_drawingImage = _insetImageList[std::stoi(index)];
		}
		_time = messageSpeed;
		_drawingByte += 3;
		DrawGraph(0, 0, _screen, true);
		return;
	}
	//経過時間からalpha値計算
	_time += _mode->GetStepTime() * 0.001f;
	int alpha = (_time - _wait) / messageSpeed * 255;
	auto camera = GetCameraViewMatrix();

	//alpha値が255未満ならBackスクリーンに半透明描画
	//255以上ならメッセージウィンドウ用のフレームバッファへ描画して描画する文字を一つ進める
	if (alpha < 255) {
		DrawGraph(0, 0, _screen, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	else {
		SetDrawScreen(_screen);
	}

	if (_drawingImage == -1) {
		DrawStringToHandle(_position.x - _messageWidth / 2 + _drawingPositionX + 2, _position.y + _drawingLine * linesSpace + shadowOffset + (_lineMax * -_fontSize / 2), s.c_str(), GetColor(0, 0, 0), _font);
		DrawStringToHandle(_position.x - _messageWidth / 2 + _drawingPositionX, _position.y + _drawingLine * linesSpace + (_lineMax * -_fontSize / 2), s.c_str(), _color, _font);
	}
	else {
		DrawExtendGraph(_position.x - _messageWidth / 2 + _drawingPositionX
			, _position.y + _drawingLine * linesSpace + (_lineMax * -_fontSize / 2)
			, _position.x - _messageWidth / 2 + _drawingPositionX + insertImageSize
			, _position.y + _drawingLine * linesSpace + (_lineMax * -_fontSize / 2) + insertImageSize
			, _drawingImage
			, true);
	}


	if (alpha < 255) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else {
		SetDrawScreen(DX_SCREEN_BACK);
		SetCameraViewMatrix(camera);
		DrawGraph(0, 0, _screen, true);

		_time = 0;
		_wait = 0;


		if (_drawingImage != -1) {
			_drawingImage = -1;
			_drawingPositionX += insertImageSize;
		}
		else {
			_drawingByte += size;
			int nextX{ _fontSize };
			GetFontCharInfo(_font, s.c_str(), nullptr, nullptr, &nextX, nullptr, nullptr);
			if (nextX == 0) {
				nextX = _fontSize;
			}
			_drawingPositionX += nextX;
		}
		if (_drawingByte >= _message.length()) {
			_messageFinished = true;
		}
	}
}

void MessageWindow::Debug()
{
	ObjectBase::Debug();
	DrawBox(_position.x - 2, _position.y - 2, _position.x + 2,_position.y + 2, GetColor(255, 0, 0), true);
}

bool MessageWindow::SetMassage(std::string name, std::string message)
{
	Init();
	_nameText = name;
	_message = message;
	_messageFinished = false;


	//中揃え用の行数を取得
	_lineMax = 1 + std::count(message.begin(), message.end(), '\n');

	//文中に挿入する画像枚数を取得
	//挿入される枚数が最も多い行を確認
	std::stringstream ss;
	ss << message;
	int insertImageCountMAX{ 0 };
	for (int i = 1; i <= _lineMax; ++i) {
		int insertImageCount{ 0 };
		std::string line;
		std::getline(ss, line);
		std::string::size_type pos = 0;
		std::string findWord = "@p";
		while ((pos = line.find(findWord, pos)) != std::string::npos) {
			++insertImageCount;
			pos += findWord.length();
		}
		if (insertImageCountMAX < insertImageCount) {
			insertImageCountMAX = insertImageCount;
		}
	}
	//中揃え用の文字幅を取得
	int cmdCount = std::count(_message.begin(), _message.end(), '@');
	if (cmdCount > 0) {
		for (int i = 0; i < cmdCount; ++i) {
			message.erase(message.begin() + message.find('@'), message.begin() + message.find('@') + 3);
		}
	}
	_messageWidth = GetDrawStringWidthToHandle(message.c_str(), message.length(), _font) + insertImageCountMAX * insertImageSize;



	int drawX, drawY, sizeX, sizeY;

	auto camera = GetCameraViewMatrix();
	SetDrawScreen(_screen);
	ClearDrawScreen();

	//メッセージウィンドウ枠を書き込んでおく
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
	int minX = _position.x - sizeW / 2;
	int minY = _position.y - sizeH / 2;
	int maxX = _position.x + sizeW / 2;
	int maxY = _position.y + sizeH / 2;
	DrawBox(minX, minY, maxX, maxY, GetColor(0, 0, 0), true);
	DrawBox(minX, minY - 50, minX + 200, minY, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//名前を書き込んでおく
	DrawStringToHandle(minX + shadowOffset, minY - linesSpace + shadowOffset, _nameText.c_str(), GetColor(0, 0, 0), _font);
	DrawStringToHandle(minX, minY - linesSpace, _nameText.c_str(), GetColor(255, 255, 255), _font);

	//アイコンを描き込んでおく
	DrawExtendGraph(minX + iconPadding, minY + iconPadding, minX + sizeH - iconPadding, maxY - iconPadding, _cg, false);

	SetDrawScreen(DX_SCREEN_BACK);
	SetCameraViewMatrix(camera);

	return true;
}