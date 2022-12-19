#include "Dummy.h"

void Dummy::Init()
{
	_scale = { 0.1f,0.1f,0.1f };
	_name = "gimmick";
	auto handle = ModelServer::LoadModel("res/DummyTarget.mv1");
	auto model = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(model));
}

void Dummy::Update(InputManager& input)
{
	ObjectBase::Update(input);
}

void Dummy::Render()
{
	ObjectBase::Render();
}
