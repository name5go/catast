/*****************************************************************//**
 * \file   ModeTest.cpp
 * \brief  モードの実装例です。ゲーム中では使用しない。
 *
 * \author 土居将太郎
 * \date   December 2022a
 *********************************************************************/
#include "PrecompiledHeader.h"
#include "ModeTest.h"
#include "TestObject.h"
#include "LevelBase.h"


 //最初に一度だけ自動的に呼ばれる
bool ModeTest::Initialize() {
	if (!ModeBase::Initialize()) { return false; }
	//テストオブジェクトの追加
	_objectServer->Add(std::make_unique<LevelBase>());
	//カメラのセット
	SetCameraPositionAndTarget_UpVecY({ 0.0f,50.0f,-150.0f }, { 0.0f,50.0f,0.0f });
	//ライトの設定
	ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
	SetLightDifColor({2.0f, 2.0f, 2.0f, 0.0f});
	return true;
}

//削除する時に一度だけ自動的に呼ばれる
bool ModeTest::Terminate() {
	ModeBase::Terminate();
	return true;

}

bool ModeTest::Update(InputManager& input) {
	ModeBase::Update(input);
	_objectServer->Update(input);

	return true;
}

bool ModeTest::Render() {
	ModeBase::Render();

	_objectServer->Render();


	return true;
}

bool ModeTest::Debug()
{
	ModeBase::Debug();
	_objectServer->Debug();
	return false;
}

