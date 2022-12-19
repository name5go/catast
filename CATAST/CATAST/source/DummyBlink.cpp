#include "DummyBlink.h"


void DummyBlink::Init()
{
	_scale = { 0.1f,0.1f,0.1f };
	_name = "gimmick";
	auto handle = ModelServer::LoadModel("res/DummyTarget.mv1");
	MV1SetMaterialDifColor(handle, 0, GetColorF(1, 1, 0, 200));
	auto model = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(model));
}

void DummyBlink::Update(InputManager& input)
{
	ObjectBase::Update(input);
}

void DummyBlink::Render()
{
	ObjectBase::Render();
}