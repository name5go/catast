/*****************************************************************//**
 * \file   DummyWarp.h
 * \brief  �����[�v�M�~�b�N
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
class DummyWarp : public ObjectBase
{
public:
	void Init()override;
	void Update(InputManager&)override;
	void Render()override;
private:
};

