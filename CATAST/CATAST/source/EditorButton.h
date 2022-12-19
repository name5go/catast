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

class EditorButton : public ObjectBase
{
public:
    void Init()override;
    void Update(InputManager&)override;
    void Render()override;
    void Debug()override;
    enum class State {
        Idle,MouseOver,Clicked
    };

    void SetActivateFunction(std::function<void(void)> func) { _activateFunction = func; }
    void SetText(std::string text);
private:
    std::function<void(void)> _activateFunction;//押された時の機能
    std::string _text;
    State _state;
    int _sizeX, _sizeY;
};