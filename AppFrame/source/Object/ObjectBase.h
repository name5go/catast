/*****************************************************************//**
 * \file   ObjectBase.h
 * \brief  �I�u�W�F�N�g�̐e�N���X
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <typeindex>

class InputManager;
class ModeBase;
class ComponentBase;
class ObjectBase {
public:
	ObjectBase();
	virtual ~ObjectBase();
	//�I�u�W�F�N�g�T�[�o�[�ɒǉ������ۂɌĂ΂��
	virtual void Init();
	//�I�u�W�F�N�g�T�[�o�[����폜���ꂽ�ۂɌĂ΂��
	virtual void Terminate();
	virtual void Update(InputManager& input);
	virtual void Render();
	virtual void Debug();

	VECTOR GetPosition() { return _position; }
	VECTOR GetRotation() { return _rotation; }
	VECTOR GetScale() { return _scale; }
	void SetPosition(VECTOR position) { _position = position; }
	void SetRotation(VECTOR rotation) { _rotation = rotation; }
	void SetScale(VECTOR scale) { _scale = scale; }
	MATRIX GetPositonMatrix() { return _positionMatrix; }
	MATRIX GetRotationMatrix() {return _rotationMatrix;}
	MATRIX GetScaleMatrix() { return _scaleMatrix; }
	MATRIX GetTransform() { return _transrom; }

	virtual bool IsDead() { return _dead; }
	virtual void Dead() { _dead = true; }

	bool GetVisible() { return _visible; }
	void SetVisible(bool flag) { _visible = flag; }
	int GetLayer() { return _layer; }
	void SetLayer(int value) { _layer = value; }
	int GetID() { return _id; }
	void SetID(int value) { _id = value; }
	std::string GetName() { return _name; }
	void SetName(std::string string) { _name = string; }
	ModeBase* GetMode() { return _mode; }
	void SetMode(ModeBase* mode) { _mode = mode; }

	void AddComponent(std::unique_ptr<ComponentBase> component);

	/**
	 * \brief �w��̃R���|�[�l���g���擾����@��FGetComponent<MV1Component>()
	 * \return �R���|�[�l���g�̃|�C���^��Ԃ��B�������Ă��Ȃ����nullptr��Ԃ��B
	 */
	template <typename C>
	C* GetComponent() {
		C* result = nullptr;
		if (_components.count(typeid(C)) != 0) {
			result = static_cast<C*>(_components[typeid(C)].get());
		}
		return result;
	}

	/**
	 * \brief �w��̃N���X���m�F����@��FCheckType<Player>()�ACheckType<Enemy>()
	 * \return �w��̃N���X�ł����true��Ԃ�
	 */
	template <typename T>
	bool CheckType() {
		if (typeid(T&) == typeid(*this)) {
			return true;
		}
		return false;
	}

	/**
	 * \brief �I�u�W�F�N�g�ԂŒʐM���s�������ꍇ�Ɏg����ėp�I�Ȋ֐��ł��B��:object->MessageEvent(*this,"damage");
	 * \param messenger ���b�Z�[�W�̔��M��
	 * \param message ���b�Z�[�W�̓��e
	 * \return �������������s������True��Ԃ�
	 */
	virtual bool MessageEvent(ObjectBase* messenger, std::string message) {
		return false;
	}

	/**  \brief �S�ẴI�u�W�F�N�g�փ��b�Z�[�W�𑗐M*/
	virtual void SendMessageAllObjects(std::string message);
	/**  \brief �I�u�W�F�N�g�փ��b�Z�[�W�𑗐M*/
	virtual void SendMessageOneObject(ObjectBase* destination,std::string message);


protected:
	bool _visible;//Render�ŕ`�悷�邩�̔���Ɏg�p

	std::string		_name;//�I�u�W�F�N�g�ɖ��O��t���Č������\
	int				_id;//�C���X�^���X�쐬���ɌŗL��ID������U����A�������\
	int				_layer;//�`�揇

	VECTOR _position;
	VECTOR _rotation;
	VECTOR _scale;
	MATRIX _positionMatrix;
	MATRIX _rotationMatrix;
	MATRIX _scaleMatrix;
	MATRIX _transrom;
	bool _dead;

	std::unordered_map<std::type_index, std::unique_ptr<ComponentBase>> _components;

	ModeBase* _mode;
};