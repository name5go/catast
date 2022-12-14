#include "ApplicationMain.h"
#include "ModeTest.h"

// 実体
ApplicationMain g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!ApplicationBase::Initialize(hInstance)) { return false; }

	// モードの登録
	ModeServer::GetInstance()->Add(std::make_unique<ModeTest>(), 1, "test");
	return true;
}

bool ApplicationMain::Terminate() {
	ApplicationBase::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	ApplicationBase::Input();
	return true;
}

bool ApplicationMain::Update() {
	if(CheckHitKey(KEY_INPUT_ESCAPE)) {
		DxLib_End();
	}
	ApplicationBase::Update();
	return true;
}

bool ApplicationMain::Render() {
	ApplicationBase::Render();
	return true;
}
