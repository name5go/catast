#include "ObjectServer.h"
#include "../Mode/ModeBase.h"
#include "Object/ObjectBase.h"
#include "ObjectBase.h"
ObjectServer::ObjectServer(ModeBase& parent)
	:_uidCount{ 0 },_mode{ parent }
{
	Clear();
}

ObjectServer::~ObjectServer()
{
	_objects.clear();
}

void ObjectServer::Clear()
{
}

void ObjectServer::Add(std::unique_ptr<ObjectBase> object)
{
	object->SetMode(&_mode);
	++_uidCount;
	object->SetID(_uidCount);
	object->Init();
	if (_updating) {
		_pendingObjects.push_back(std::move(object));
	}
	else {
		_objects.push_back(std::move(object));
	}
}

void ObjectServer::Delete(ObjectBase& object)
{
	object.Dead();
}

namespace {
	static bool objectSort(std::unique_ptr<ObjectBase>& x, std::unique_ptr<ObjectBase>& y) {
		return x->GetLayer() < y->GetLayer();
	}
}

void ObjectServer::Update(InputManager& input)
{
	_updating = true;
	DeleteObject();	// 削除予約されたオブジェクトを削除する
	AddPendingObject();
	std::sort(_objects.begin(), _objects.end(), objectSort);

	for (auto&& actor : _objects) {
		actor->Update(input);
	}
	_updating = false;

}

void ObjectServer::Render()
{
	for (auto&& actor : _objects) {
		actor->Render();
	}
}

void ObjectServer::Debug()
{
	for (auto&& actor : _objects) {
		actor->Debug();
	}
}

ObjectBase* ObjectServer::Get(int id)
{
	for (auto&& object : _objects) {
		if (object->GetID() == id) {
			return object.get();
		}
	}
	return nullptr;
}

ObjectBase* ObjectServer::Get(std::string name)
{
	for (auto&& object : _objects) {
		if (object->GetName() == name) {
			return object.get();
		}
	}
	return nullptr;
}

void ObjectServer::AddPendingObject()
{
	// Add()されたものを有効にし、必要であればソートを行う
	if (_pendingObjects.size() > 0) {
		auto ite = _pendingObjects.begin();
		for (; ite != _pendingObjects.end(); ++ite) {
			_objects.push_back(std::move((*ite)));
		}
		_pendingObjects.clear();
	}
}

void ObjectServer::DeleteObject()
{
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for (auto ite = _objects.begin(); ite != _objects.end(); ) {
		if ((*ite)->IsDead()) {
			(*ite)->Terminate();
			ite = _objects.erase(ite);		// これでobjectそのものも削除される
		}
		else {
			++ite;
		}
	}
}