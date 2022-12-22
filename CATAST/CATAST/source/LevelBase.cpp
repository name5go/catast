/*****************************************************************//**
 * \file   LevelBase.cpp
 * \brief  
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/


void LevelBase::Init()
{
	//ModelServerを使って3Dモデルのハンドルを取得
	auto handle = ModelServer::LoadModel("res/LevelModel/LevelBase.mv1");
	//auto handle = ModelServer::LoadModel("res/Player/Model/Player.mv1");
	//3Dモデル(MV1)の描画機能を持つMV1Componentを追加する。
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void LevelBase::Update(InputManager&input)
{
	//ここで_componentsに登録しているコンポーネントのUpdateを呼んでいる。つまり3Dモデルの位置やアニメーションが更新される。
	ObjectBase::Update(input);
}

void LevelBase::Render()
{
	//ここで_componentsに登録しているコンポーネントのRenderを呼んでいる。つまり3Dモデルが描画される。
	ObjectBase::Render();

}
