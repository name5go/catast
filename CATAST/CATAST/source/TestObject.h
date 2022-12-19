/*****************************************************************//**
 * \file   TestObject.h
 * \brief  オブジェクトの実装例です。ゲーム中では使用しない。
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once

class TestObject : public ObjectBase
{
public:
    void Init()override;
    void Update(InputManager&)override;
    void Render()override;
private:

};

