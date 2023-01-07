/*****************************************************************//**
 * \file   ObjectBase.h
 * \brief  オブジェクトの親クラス
 *
 * \author 土居将太郎
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
	//オブジェクトサーバーに追加した際に呼ばれる
	virtual void Init();
	//オブジェクトサーバーから削除された際に呼ばれる
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
	 * \brief 指定のコンポーネントを取得する　例：GetComponent<MV1Component>()
	 * \return コンポーネントのポインタを返す。所持していなければnullptrを返す。
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
	 * \brief 指定のクラスか確認する　例：CheckType<Player>()、CheckType<Enemy>()
	 * \return 指定のクラスであればtrueを返す
	 */
	template <typename T>
	bool CheckType() {
		if (typeid(T&) == typeid(*this)) {
			return true;
		}
		return false;
	}

	/**
	 * \brief オブジェクト間で通信を行いたい場合に使える汎用的な関数です。例:object->MessageEvent(*this,"damage");
	 * \param messenger メッセージの発信元
	 * \param message メッセージの内容
	 * \return 正しく処理を行えたらTrueを返す
	 */
	virtual bool MessageEvent(ObjectBase* messenger, std::string message) {
		return false;
	}

	/**  \brief 全てのオブジェクトへメッセージを送信*/
	virtual void SendMessageAllObjects(std::string message);
	/**  \brief オブジェクトへメッセージを送信*/
	virtual void SendMessageOneObject(ObjectBase* destination,std::string message);


protected:
	bool _visible;//Renderで描画するかの判定に使用

	std::string		_name;//オブジェクトに名前を付けて検索が可能
	int				_id;//インスタンス作成時に固有のIDが割り振られる、検索が可能
	int				_layer;//描画順

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