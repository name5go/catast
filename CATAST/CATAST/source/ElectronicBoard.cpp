#include "ElectronicBoard.h"

ElectronicBoard::ElectronicBoard()
	:_flag{ true }
	, _screenHandle{ -1 }
	, _baseTex{ -1 }
	, _brightness{ 1.0f }
	, _gridNumber{ 32 }
	, _fxIndex{ 0 }
	, _fxX{ 0 }, _fxY{ 0 }
{
	_position = { 30.0f,0.0f,0.0f };
	_scale = { 3.0f,3.0f,3.0f };
	_name = "gimmick";
}

ElectronicBoard::~ElectronicBoard()
{
	DeleteShaderConstantBuffer(_testHandle);
	DeleteShader(_vHandle);
	DeleteShader(_pHandle);
}

void ElectronicBoard::Init()
{
	SetCameraNearFar(0.1f, 1000.0f);
	_screenHandle = MakeScreen(256, 256, true);
	_baseTex = ImageServer::LoadGraph("res/StageImage/StageBase.png");
	_moveTex = ImageServer::LoadGraph("res/StageImage/StageFX.png");
	_fx.resize(3);
	ImageServer::LoadDivGraph("res/StageImage/StageFX2.png", 3, 3, 1, 64, 64, _fx.data());

	auto handle = ModelServer::LoadModel("res/StageImage/ElectronicBoard.mv1");
	auto mv1 = std::make_unique<MV1Component>(handle);
	//�e�N�X�`���ύX
	MV1SetTextureGraphHandle(handle, 0, _baseTex, false);
	MV1SetTextureGraphHandle(handle, 1, _moveTex, true);
	MV1SetTextureGraphHandle(handle, 2, _screenHandle, true);

	AddComponent(std::move(mv1));

	// �V�F�[�_�[��K��
	_vHandle = LoadVertexShader("res/Shader/vertex_shader.vso");
	_pHandle = LoadPixelShader("res/Shader/ElectronicBoardPS.pso");

	SetUseVertexShader(_vHandle);
	SetUsePixelShader(_pHandle);

	// �s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���쐬
	_testHandle = CreateShaderConstantBuffer(sizeof(float) * 4);

}

void ElectronicBoard::Update(InputManager& input)
{
	ObjectBase::Update(input);
	if (input.GetKeyUp(InputState::Hold)) {
		_brightness += 0.1f;
	}
	if (input.GetKeyDown(InputState::Hold)) {
		_brightness -= 0.1f;
	}
	if (input.GetKeyRight(InputState::Pressed)) {
		_gridNumber += 1;
	}
	if (input.GetKeyLeft(InputState::Pressed)) {
		_gridNumber -= 1;
	}
	if (_mode->GetModeCount() % 60 == 0) {
		++_fxIndex;
		if (_fxIndex > 2) {
			_fxIndex = 0;
		}
	}

	VECTOR screenPosStart{ static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()),0.0f };
	VECTOR screenPosEnd{ static_cast<float>(input.GetMouseX()),static_cast<float>(input.GetMouseY()),1.0f };
	VECTOR worldPosStart{ ConvScreenPosToWorldPos(screenPosStart) };
	VECTOR worldPosEnd{ ConvScreenPosToWorldPos(screenPosEnd) };
	_fxX = -9999;
	_fxY = -9999;
	int handle = GetComponent<MV1Component>()->GetModelHandle();
	MV1RefreshCollInfo(handle, -1);
	auto result = MV1CollCheck_Line(handle, -1, worldPosStart, worldPosEnd);
	if (result.HitFlag) {

		_fxX = (result.HitPosition.x - _position.x) * 4;
		_fxY = (1 - (result.HitPosition.y - _position.y)) * 4;
	}
}

void ElectronicBoard::Render()
{


	//�J�����ݒ肪���Z�b�g�����̂ŕۑ�
	auto cameraMat = GetCameraViewMatrix();
	auto cameraNear = GetCameraNear();
	auto cameraFar = GetCameraFar();
	////�e�N�X�`���p�̃X�N���[���i�t���[���o�b�t�@�j�֏�������
	SetDrawScreen(_screenHandle);
	ClearDrawScreen();
	DrawExtendGraph(_fxX, _fxY, _fxX + 256, _fxY + 256, _fx[_fxIndex], true);
	SetDrawScreen(DX_SCREEN_BACK);
	//�J�����ݒ�����ɖ߂�
	SetCameraViewMatrix(cameraMat);
	SetCameraNearFar(cameraNear, cameraFar);


	if (_flag) {
		MV1SetUseOrigShader(TRUE);
		// �s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
		auto bufferAdress = (FLOAT4*)GetBufferShaderConstantBuffer(_testHandle);
		if (bufferAdress != nullptr) {
			// ���W�l���擾�����A�h���X�ɏ�������
			bufferAdress->x = static_cast<float>(_mode->GetModeTime() * 0.001f * 2.0);
			bufferAdress->y = static_cast<float>(_brightness);
			bufferAdress->z = static_cast<float>(_gridNumber);
			// ���_�V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
			UpdateShaderConstantBuffer(_testHandle);
			// ���_�V�F�[�_�[�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�S�ɃZ�b�g
			SetShaderConstantBuffer(_testHandle, DX_SHADERTYPE_PIXEL, 2);
		}
		ObjectBase::Render();
		MV1SetUseOrigShader(FALSE);
		DrawGraph(0, 0, _baseTex, false);
		DrawGraph(0, 300, _moveTex, false);
		DrawGraph(0, 600, _screenHandle, false);
	}
	else {
		ObjectBase::Render();
	}
}

void ElectronicBoard::Debug()
{
	std::stringstream ss;
	ss <<"�P�x" << _brightness<<"\n";
	ss << "������" << _gridNumber;
	DrawString(0, 1000, ss.str().c_str(), GetColor(255, 255, 255));

	DrawFormatString(300, 150, GetColor(255, 255, 255), "�������Ȃ��e�N�X�`��");
	DrawFormatString(300, 450, GetColor(255, 255, 255), "�����ɗ����e�N�X�`��\n�i�ق�Ƃ͓��߂��Ă�j");
	DrawFormatString(300, 600, GetColor(255, 255, 255), "���}�E�X�̍��W�ʒu��\n�G�t�F�N�g�u���e�N�X�`��\n�i�ق�Ƃ͓��߂��Ă�j\n�G�t�F�N�g�̓X�v���C�g�V�[�g");
}
