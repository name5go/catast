/*****************************************************************//**
 * \file   TestObject.cpp
 * \brief  オブジェクトの実装例です。ゲーム中では使用しない。
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/


//最初に一度だけ自動的に呼ばれる
void TestObject::Init()
{
	_scale={ 0.3f,0.3f,0.3f };
	//ModelServerを使って3Dモデルのハンドルを取得
	auto handle = ModelServer::LoadModel("res/character/SDChar.mv1");
	//3Dモデル(MV1)の描画機能を持つMV1Componentを追加する。
	auto mv1Component = std::make_unique<MV1Component>(handle);

	//パンチのSE
	auto seFunc = [] {PlaySoundMem(SoundServer::LoadSE("res/character/Punch.mp3"), DX_PLAYTYPE_BACK);};
	//2番のアニメーションの11.7秒に仕込む
	mv1Component->AddAnimFunction(2, 11.7f, seFunc);
	//足音のSE
	auto seFunc2 = [] {PlaySoundMem(SoundServer::LoadSE("res/character/Walk.mp3"), DX_PLAYTYPE_BACK); };
	//1番のアニメーションの6.23秒、25.9秒に仕込む
	mv1Component->AddAnimFunction(1, 6.23f, seFunc2);
	mv1Component->AddAnimFunction(1, 25.9f, seFunc2);

	mv1Component->SetAnimation(2);
	AddComponent(std::move(mv1Component));
	PlaySoundMem(SoundServer::LoadSE("res/character/Punch.mp3"), DX_PLAYTYPE_BACK);
}

void TestObject::Update(InputManager& input)
{
	//ここで_componentsに登録しているコンポーネントのUpdateを呼んでいる。つまり3Dモデルの位置やアニメーションが更新される。
	ObjectBase::Update(input);

	//キーボードのAを押した瞬間にifの中に入る
	if (input.GetKeyA(InputState::Pressed)) {
		//MV1コンポーネントにアニメーション再生機能があるのでアニメーションの0番を再生するように設定
		GetComponent<MV1Component>()->SetAnimation(1);
	}

	//キーボードのAを押した瞬間にifの中に入る
	if (input.GetKeyS(InputState::Pressed)) {
		//MV1コンポーネントにアニメーション再生機能があるのでアニメーションの0番を再生するように設定
		GetComponent<MV1Component>()->SetAnimation(2);
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

}
