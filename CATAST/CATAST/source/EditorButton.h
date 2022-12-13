/*****************************************************************//**
 * \file   EditorButton.h
 * \brief  ステージエディタ用ボタン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <functional>
class ObjectListWindow;

class EditorButton : public ObjectBase
{
public:
	EditorButton(ObjectListWindow&);
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
	void Debug()override;
	enum class State {
		Idle, MouseOver, Clicked
	};

	void SetActivateFunction(std::function<void(ObjectListWindow*)> func) { _activateFunction = func; }
	void SetNonActivateFunction(std::function<void(ObjectListWindow*)> func) { _nonactivateFunction = func; }
	void SetText(std::string text);
	void SetToggle(bool flag) { _toggle = flag; }
	bool MessageEvent(ObjectBase* messenger,std::string message)override;
	void SetVisibleMessage(std::string msg) { _visibleMessage = msg; }
	void SetInvisibleMessage(std::string msg) { _invisibleMessage = msg; }
	void SetUnpushedMessage(std::string msg) { _unPushedMessage = msg; }
private:
	std::function<void(ObjectListWindow*)> _activateFunction;//押された時の機能
	std::function<void(ObjectListWindow*)> _nonactivateFunction;//OFFになった時の機能(トグル式の時のみ使用)
	std::string _invisibleMessage;
	std::string _visibleMessage;
	std::string _unPushedMessage;
	std::string _text;
	State _state;
	int _sizeX, _sizeY;
	ObjectListWindow& _list;
	bool _toggle;//ボタンをトグル式にするフラグ
};