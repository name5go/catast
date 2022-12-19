/*****************************************************************//**
 * \file   ModeInGame.cpp
 * \brief  インゲーム部分です
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/
#include "PrecompiledHeader.h"




bool ModeInGame::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	//オブジェクトの追加
	_objectServer->Add(std::make_unique<LevelBase>());

	//_objectServer->Add(std::make_unique<LevelBase>());
	//カメラのセット
	SetCameraPositionAndTarget_UpVecY({ 0.0f,50.0f,-150.0f }, { 0.0f,50.0f,0.0f });
	//ライトの設定
	ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
	SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });
	return false;
}

bool ModeInGame::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeInGame::Update(InputManager& input)
{
	ModeBase::Update(input);
	_objectServer->Update(input);

	return false;
}

bool ModeInGame::Render()
{
	ModeBase::Render();

	_objectServer->Render();
	return false;
}

bool ModeInGame::Debug()
{
	ModeBase::Debug();
	_objectServer->Debug();
	return false;
}
