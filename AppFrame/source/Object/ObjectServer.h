
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

	/** Actor���y���f�B���O�ɒǉ����� */
	void Add(std::unique_ptr<ObjectBase> actor);
	//����̃I�u�W�F�N�g���폜����
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

	//�y���f�B���O��Actor���Q�[�����ɒǉ�
	void AddPendingObject();
	//dead�t���O�������Ă���I�u�W�F�N�g��S�č폜
	void DeleteObject();

	int _uidCount;
	ModeBase& _mode;
};