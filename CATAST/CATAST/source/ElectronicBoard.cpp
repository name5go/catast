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
	//テクスチャ変更
	MV1SetTextureGraphHandle(handle, 0, _baseTex, false);
	MV1SetTextureGraphHandle(handle, 1, _moveTex, true);
	MV1SetTextureGraphHandle(handle, 2, _screenHandle, true);

	AddComponent(std::move(mv1));

	// シェーダーを適応
	_vHandle = LoadVertexShader("res/Shader/vertex_shader.vso");
	_pHandle = LoadPixelShader("res/Shader/ElectronicBoardPS.pso");

	SetUseVertexShader(_vHandle);
	SetUsePixelShader(_pHandle);

	// ピクセルシェーダー用の定数バッファを作成
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


	//カメラ設定がリセットされるので保存
	auto cameraMat = GetCameraViewMatrix();
	auto cameraNear = GetCameraNear();
	auto cameraFar = GetCameraFar();
	////テクスチャ用のスクリーン（フレームバッファ）へ書き込む
	SetDrawScreen(_screenHandle);
	ClearDrawScreen();
	DrawExtendGraph(_fxX, _fxY, _fxX + 256, _fxY + 256, _fx[_fxIndex], true);
	SetDrawScreen(DX_SCREEN_BACK);
	//カメラ設定を元に戻す
	SetCameraViewMatrix(cameraMat);
	SetCameraNearFar(cameraNear, cameraFar);


	if (_flag) {
		MV1SetUseOrigShader(TRUE);
		// ピクセルシェーダー用の定数バッファのアドレスを取得
		auto bufferAdress = (FLOAT4*)GetBufferShaderConstantBuffer(_testHandle);
		if (bufferAdress != nullptr) {
			// 座標値を取得したアドレスに書き込み
			bufferAdress->x = static_cast<float>(_mode->GetModeTime() * 0.001f * 2.0);
			bufferAdress->y = static_cast<float>(_brightness);
			bufferAdress->z = static_cast<float>(_gridNumber);
			// 頂点シェーダー用の定数バッファを更新して書き込んだ内容を反映する
			UpdateShaderConstantBuffer(_testHandle);
			// 頂点シェーダーの定数バッファを定数バッファレジスタ４にセット
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
	ss <<"輝度" << _brightness<<"\n";
	ss << "分割数" << _gridNumber;
	DrawString(0, 1000, ss.str().c_str(), GetColor(255, 255, 255));

	DrawFormatString(300, 150, GetColor(255, 255, 255), "←動かないテクスチャ");
	DrawFormatString(300, 450, GetColor(255, 255, 255), "←横に流れるテクスチャ\n（ほんとは透過してる）");
	DrawFormatString(300, 600, GetColor(255, 255, 255), "←マウスの座標位置に\nエフェクト置くテクスチャ\n（ほんとは透過してる）\nエフェクトはスプライトシート");
}
