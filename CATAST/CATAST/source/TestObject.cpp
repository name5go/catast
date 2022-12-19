/*****************************************************************//**
 * \file   TestObject.cpp
 * \brief  オブジェクトの実装例です。ゲーム中では使用しない。
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "TestObject.h"
#include <sstream>

//最初に一度だけ自動的に呼ばれる
void TestObject::Init()
{
	//ModelServerを使って3Dモデルのハンドルを取得
	auto handle = ModelServer::LoadModel("res/ridgidSimTest.mv1");
	//3Dモデル(MV1)の描画機能を持つMV1Componentを追加する。
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void TestObject::Update(InputManager& input)
{
	//ここで_componentsに登録しているコンポーネントのUpdateを呼んでいる。つまり3Dモデルの位置やアニメーションが更新される。
	ObjectBase::Update(input);

	//キーボードのAを押した瞬間にifの中に入る
	if (input.GetKeyA(InputState::Pressed)) {
		//MV1コンポーネントにアニメーション再生機能があるのでアニメーションの0番を再生するように設定
		GetComponent<MV1Component>()->SetAnimation(0);
	}

	//キーボードの右を押している間ifの中に入る
	if (input.GetKeyRight(InputState::Hold)) {
		//X軸方向に1.0動かす
		_position = VAdd(_position, { 1.0f,0.0f,0.0f });
	}
	//キーボードの左を押している間ifの中に入る
	else if (input.GetKeyLeft(InputState::Hold)) {
		//X軸方向に-1.0動かす
		_position = VSub(_position, { 1.0f,0.0f,0.0f });
	}
}

void TestObject::Render()
{
	//ここで_componentsに登録しているコンポーネントのRenderを呼んでいる。つまり3Dモデルが描画される。
	ObjectBase::Render();

	std::stringstream ss;
	ss << "左右キーで移動　Aキーでアニメーション再生";
	DrawString(0, 0, ss.str().c_str(), GetColor(255, 255, 255));
}

//テストです