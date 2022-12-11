
#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <string>

class ObjectBase;
class InputManager;
class ModeBase;

class ObjectServer {

public:
	ObjectServer(ModeBase& parent);
	~ObjectServer();

	std::vector<std::unique_ptr<ObjectBase>>& GetObjects() { return _objects; }

	void Clear();

	/** Actorをペンディングに追加する */
	void Add(std::unique_ptr<ObjectBase> actor);
	//特定のオブジェクトを削除する
	void Delete(ObjectBase& actor);
	void Update(InputManager& input);
	void Render();
	void Debug();

	ObjectBase* Get(int id);
	ObjectBase* Get(std::string name);

private:
	std::vector<std::unique_ptr<ObjectBase>> _objects;
	std::vector<std::unique_ptr<ObjectBase>> _pendingObjects;

	bool _updating;

	//ペンディングのActorをゲーム内に追加
	void AddPendingObject();
	//deadフラグが立っているオブジェクトを全て削除
	void DeleteObject();

	int _uidCount;
	ModeBase& _mode;
};