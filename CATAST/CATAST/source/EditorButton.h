/*****************************************************************//**
 * \file   EditorButton.h
 * \brief  �X�e�[�W�G�f�B�^�p�{�^��
 * 
 * \author �y�������Y
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
    std::function<void(void)> _activateFunction;//�����ꂽ���̋@�\
    std::string _text;
    State _state;
    int _sizeX, _sizeY;
};