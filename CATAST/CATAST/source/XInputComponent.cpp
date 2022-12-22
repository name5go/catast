#include "XInputComponent.h"
/*****************************************************************//**
 * \file   InputComponent.cpp
 * \brief  �C���v�b�g���A�X�e�B�b�N����x�N�g����rad�Ƃ��擾
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/

XInputComponent::XInputComponent()
{
	
}

XInputComponent::~XInputComponent()
{
}

bool XInputComponent::Init()
{
	_stickTilt_Length_R = 0;
	_stickTilt_Length_L = 0;
	_stickTilt_Rad_R = 0;
	_stickTilt_Rad_L = 0;
	_trg_L2 = 0;
	_trg_R2 = 0;

	return true;
}

void XInputComponent::Update()
{
	//xInput�X�V
	GetJoypadXInputState(DX_INPUT_PAD1, &_xinput);
	//�R���g���[���[�̌X��{x��( -32768 �` 32767 ),y��( -32768 �` 32767 )}��1000�ł��������ɂ���
	float adapt = 1.0f/1000.0f;
	float y_R = static_cast<float>(_xinput.ThumbRY) * adapt;
	float x_R = static_cast<float>(_xinput.ThumbRX) * adapt;

	float y_L = static_cast<float>(_xinput.ThumbLY) * adapt;
	float x_L = static_cast<float>(_xinput.ThumbLX) * adapt;

	_stickTilt_Rad_R = atan2f(y_R, x_R);
	_stickTilt_Length_R = sqrt(x_R * x_R + y_R * y_R);

	_stickTilt_Rad_L = atan2f(y_L, x_L);
	_stickTilt_Length_L = sqrt(x_L * x_L + y_L * y_L);
	
	//�g���K�[�̓��͊��x
	_trg_R2 = static_cast<int>(_xinput.RightTrigger);
	_trg_L2 = static_cast<int>(_xinput.LeftTrigger);
}

void XInputComponent::Render()
{
}

void XInputComponent::Debug()
{
}

std::pair<float, float> XInputComponent::GetStickLenRad(Stick LR)
{
	switch (LR)
	{
	case Stick::L:
		return{ _stickTilt_Length_L ,_stickTilt_Rad_L };
	case Stick::R:
		return{ _stickTilt_Length_R ,_stickTilt_Rad_R };
	default:
		return { 0,0 };
	}
}





