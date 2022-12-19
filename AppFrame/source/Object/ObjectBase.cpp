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
#include "ObjectServer.h"

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
		_positionMatrix = MGetTranslate(_position);
		_rotationMatrix = MMult(MMult(MGetRotX(_rotation.x), MGetRotY(_rotation.y)), MGetRotZ(_rotation.z));
		_scaleMatrix = MGetScale(_scale);
		
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

	void ObjectBase::SendMessageAllObjects(std::string message)
	{
		for (auto&& object : _mode->GetObjectServer()->GetObjects()) {
			object->MessageEvent(this, message);
		}
	}

	void ObjectBase::SendMessageOneObject(ObjectBase* destination, std::string message)
	{
		destination->MessageEvent(this, message);
	}
