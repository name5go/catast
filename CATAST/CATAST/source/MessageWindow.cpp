/*****************************************************************//**
 * \file   MessageWindow.cpp
 * \brief  ���b�Z�[�W���\�������E�B���h�E
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
namespace {
	constexpr int sizeW = 1100;
	constexpr int sizeH = 200;
	constexpr float positionYRaito = 0.85f;//Y�ʒu����p�A�E�B���h�E�̏c�T�C�Y�ɑ΂��Ă̔䗦
	constexpr int iconPadding = 50;//�L�����摜����̋󔒂̑傫��
	constexpr float messageSpeed = 0.05f;//1�����t�F�[�h�C������̂Ɏg�p���鎞��sec
	constexpr int linesSpace = 40;//�s��px
	constexpr int shadowOffset = 2;//�����e���E���ւ��炷��px
	constexpr int insertImageSize = 32;//�����ɑ}������摜�T�C�YXYpx
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

	SetMassage("�_�~�[����", "����ɂ���@p0����΂��@c1\nABCD123456789");
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
		SetMassage("�_�~�[����", "����@p0 \n�ɂ�\n��@w1��");
	}
	if (input.GetKeyZ(InputState::Pressed)) {
		SetMassage("�_�~�[����", "�{�N���i�ʂ�@c2������@c1������A\n�S��芴�Ӑ\�������܂��B");
	}
	if (input.GetKeyC(InputState::Pressed)) {
		SetMassage("�_�~�[����", "Eigo Ha Douse Kakanyaro\n13246789");
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

	int size = 0;//1����������̃o�C�g��

	size = ShiftJISChecker::Check(_message[_drawingByte]);

	//s�ɕ`�悷�镶��������
	std::string s = "";
	for (int i = 0; i < size; i++) {
		s += _message[_drawingByte + i];
	}

	//\n�Ȃ���s���ďI���
	if (s == "\n") {
		++_drawingLine;
		_drawingPositionX = 0;
		_time = messageSpeed;
		_drawingByte += size;
		DrawGraph(0, 0, _screen, true);
		return;
	}
	//@�Ȃ�R�}���h�ǂݍ���
	if (s == "@") {
		//2byte��܂ł̓R�}���h���e
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
	//�o�ߎ��Ԃ���alpha�l�v�Z
	_time += _mode->GetStepTime() * 0.001f;
	int alpha = (_time - _wait) / messageSpeed * 255;
	auto camera = GetCameraViewMatrix();

	//alpha�l��255�����Ȃ�Back�X�N���[���ɔ������`��
	//255�ȏ�Ȃ烁�b�Z�[�W�E�B���h�E�p�̃t���[���o�b�t�@�֕`�悵�ĕ`�悷�镶������i�߂�
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


	//�������p�̍s�����擾
	_lineMax = 1 + std::count(message.begin(), message.end(), '\n');

	//�����ɑ}������摜�������擾
	//�}������閇�����ł������s���m�F
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
	//�������p�̕��������擾
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

	//���b�Z�[�W�E�B���h�E�g����������ł���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
	int minX = _position.x - sizeW / 2;
	int minY = _position.y - sizeH / 2;
	int maxX = _position.x + sizeW / 2;
	int maxY = _position.y + sizeH / 2;
	DrawBox(minX, minY, maxX, maxY, GetColor(0, 0, 0), true);
	DrawBox(minX, minY - 50, minX + 200, minY, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//���O����������ł���
	DrawStringToHandle(minX + shadowOffset, minY - linesSpace + shadowOffset, _nameText.c_str(), GetColor(0, 0, 0), _font);
	DrawStringToHandle(minX, minY - linesSpace, _nameText.c_str(), GetColor(255, 255, 255), _font);

	//�A�C�R����`������ł���
	DrawExtendGraph(minX + iconPadding, minY + iconPadding, minX + sizeH - iconPadding, maxY - iconPadding, _cg, false);

	SetDrawScreen(DX_SCREEN_BACK);
	SetCameraViewMatrix(camera);

	return true;
}