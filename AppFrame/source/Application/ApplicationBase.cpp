#include "ApplicationBase.h"
#include "../Mode//ModeServer.h"
#include "../Input/InputManager.h"

ApplicationBase* ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
	_modeServer = nullptr;
	_inputManager = nullptr;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {
	SetOutApplicationLogValidFlag(FALSE);
	// DXライブラリの初期化
	if (AppWindowed()) {
		ChangeWindowMode(true);							// ウィンドウモードに指定する
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);
	SetAlwaysRunFlag(true);
	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_modeServer.reset(new ModeServer);
	//インプットマネージャーの初期化
	_inputManager.reset(new InputManager);

	return true;
}

bool ApplicationBase::Terminate() {
	// DXライブラリ開放
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// キーの入力、トリガ入力を得る
	_inputManager->Input();
	return true;
}

bool ApplicationBase::Update() {
	_modeServer->UpdateInit();
	_modeServer->Update(*_inputManager);
	_modeServer->UpdateFinish();
	return true;
}

bool ApplicationBase::Render() {
	_modeServer->RenderInit();
	_modeServer->Render();
	_modeServer->RenderFinish();
	_modeServer->DebugInit();
	_modeServer->Debug();
	_modeServer->RenderFinish();
	return true;
}