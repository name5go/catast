/*****************************************************************//**
 * \file   CameraCompornent.h
 * \brief  �J��������p�̃R���|�[�l���g
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/
#pragma once


class CameraComponent:public ComponentBase
{
public:
	CameraComponent();
	~CameraComponent();
	virtual bool Init();
	virtual void Update();
	virtual void Render();
	virtual void Debug();

protected:
	ObjectBase* _parent;

private:

};

