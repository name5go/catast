#include "DummyBounce.h"

void DummyBounce::Init()
{
	_scale = { 0.1f,0.1f,0.1f };
	_name = "gimmick";
	auto handle = ModelServer::LoadModel("res/DummyTarget.mv1");
	MV1SetMaterialDifColor(handle, 0, GetColorF(1.0, 0.5, 0, 1));
	auto model = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(model));
}

void DummyBounce::Update(InputManager& input)
{
	ObjectBase::Update(input);
}

void DummyBounce::Render()
{
	ObjectBase::Render();
}