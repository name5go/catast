/*****************************************************************//**
 * \file   DummyBounce.h
 * \brief  �����˃M�~�b�N
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyBounce : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

