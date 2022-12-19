#include "DummyWarp.h"

void DummyWarp::Init()
{
	_scale = { 0.1f,0.1f,0.1f };
	_name = "gimmick";
	auto handle = ModelServer::LoadModel("res/DummyTarget.mv1");
	MV1SetMaterialDifColor(handle, 0, GetColorF(0, 0, 1, 1));
	auto model = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(model));
}

void DummyWarp::Update(InputManager& input)
{
	ObjectBase::Update(input);
}

void DummyWarp::Render()
{
	ObjectBase::Render();
}
