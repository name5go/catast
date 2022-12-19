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
	// DX���C�u�����̏�����
	if (AppWindowed()) {
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);
	SetAlwaysRunFlag(true);
	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_modeServer.reset(new ModeServer);
	//�C���v�b�g�}�l�[�W���[�̏�����
	_inputManager.reset(new InputManager);

	return true;
}

bool ApplicationBase::Terminate() {
	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
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
	_modeServer->DebugFinish();
	return true;
}