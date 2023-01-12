#include "Dummy.h"
/*****************************************************************//**
 * \file   Dummy.cpp
 * \brief  仮ターゲット
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
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

bool Dummy::MessageEvent(ObjectBase* obj, std::string msg)
{
	if (obj == nullptr) {
		return false;
	}
	if (obj->CheckType<Player>() && msg == "hit") {
		auto selfModelHandle =GetComponent<MV1Component>()->GetModelHandle();
		if (obj->GetComponent<CollisionComponent>()->Intersect(selfModelHandle)) {
			Dead();
			return true;
		}
	}
	return false;
}
