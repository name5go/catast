/*****************************************************************//**
 * \file   Player.cpp
 * \brief  
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/

Player::Player()
{
	_scale = {0.01f, 0.01f, 0.01f};
	
}
Player::~Player()
{

}

void Player::Init()
{
	//ModelServerを使って3Dモデルのハンドルを取得
	auto handle = ModelServer::LoadModel("res/Player/Model/Player.mv1");
	//3Dモデル(MV1)の描画機能を持つMV1Componentを追加する。
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
	//camera機能を持たせる
	float cameraDistance = 3.0;
	auto cameraComponent = std::make_unique<CameraComponent>(cameraDistance);
	AddComponent(std::move(cameraComponent));
	//動く時の速度と動き方を指定
	float movePower=0.5f;
	auto xinputMoveComponent = std::make_unique<XInputMoveComponent>(movePower,MoveType::As_3D,CameraType::TPS);
	AddComponent(std::move(xinputMoveComponent));

	_rotation = { 0.0f,Math::ToRadians(180.0f),0.0f};
}

void Player::Update(InputManager&input)
{

	//ここで_componentsに登録しているコンポーネントのUpdateを呼んでいる。つまり3Dモデルの位置やアニメーションが更新される。
	ObjectBase::Update(input);

}

void Player::Render()
{
	//ここで_componentsに登録しているコンポーネントのRenderを呼んでいる。つまり3Dモデルが描画される。
	ObjectBase::Render();
}
