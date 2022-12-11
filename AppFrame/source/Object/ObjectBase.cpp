/*****************************************************************//**
 * \file   ObjectBase.cpp
 * \brief  オブジェクトの親クラス
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#include "ObjectBase.h"
#include "Resource/ModelServer.h"
#include "../Mode/ModeBase.h"
#include "ComponentBase.h"

	ObjectBase::ObjectBase()
		: _position{ 0,0,0 }
		, _rotation{ 0,0,0 }
		, _scale{ 1,1,1 }
		, _dead{ false }
		, _visible{ true }
		, _name{ "null" }
		, _id{ -1 }
		, _layer{ 0 }
	{
		
	}

	ObjectBase::~ObjectBase()
	{
		_components.clear();
	}

	void ObjectBase::Init()
	{
	}

	void ObjectBase::Terminate()
	{
		//_components.clear();
	}

	void ObjectBase::Update(InputManager& input)
	{
		for (auto&& component : _components) {
			component.second->Update();
		}
	}

	void ObjectBase::Render()
	{
		if (!_visible) {
			return;
		}
		for (auto&& component : _components) {
			component.second->Render();
		}
	}

	void ObjectBase::Debug()
	{
		for (auto&& component : _components) {
			component.second->Debug();
		}
	}

	void ObjectBase::AddComponent(std::unique_ptr<ComponentBase> component)
	{
		component->SetParent(this);
		if (component->Init()) {
			_components[typeid(*component)] = (std::move(component));
		}
	}