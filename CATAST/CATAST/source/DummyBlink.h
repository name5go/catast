/*****************************************************************//**
 * \file   DummyBlink.h
 * \brief  �������M�~�b�N
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyBlink :
    public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

