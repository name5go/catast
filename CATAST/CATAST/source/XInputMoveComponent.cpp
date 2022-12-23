/*****************************************************************//**
 * \file   InputComponent.cpp
 * \brief  �C���v�b�g���A�X�e�B�b�N����x�N�g����rad�Ƃ��擾
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/

XInputMoveComponent::XInputMoveComponent(float power,Moving type)
{
	_movePower = power;
	_movetype = type;
}

XInputMoveComponent::~XInputMoveComponent()
{
}

bool XInputMoveComponent::Init()
{



	return true;
}

void XInputMoveComponent::Update()
{
	//xInput�X�V
	GetJoypadXInputState(DX_INPUT_PAD1, &_xinput);
}

void XInputMoveComponent::Render()
{
}

void XInputMoveComponent::Debug()
{
}

std::pair<float, float> XInputMoveComponent::GetStickLenRad(Side LR)
{
	//�R���g���[���[�̌X��{x��( -32768 �` 32767 ),y��( -32768 �` 32767 )}��1000�Ŋ�����float�Ōv�Z����p�ɂ��������ɂ���
	float adapt = 1.0f / 1000.0f;
	switch (LR)
	{
	case Side::L:
		float y_L = static_cast<float>(_xinput.ThumbLY) * adapt;
		float x_L = static_cast<float>(_xinput.ThumbLX) * adapt;
		return{ sqrt(x_L * x_L + y_L * y_L) ,atan2f(y_L, x_L) };
	case Side::R:
		float y_R = static_cast<float>(_xinput.ThumbRY) * adapt;
		float x_R = static_cast<float>(_xinput.ThumbRX) * adapt;
		return{ sqrt(x_R * x_R + y_R * y_R) ,atan2f(y_R, x_R) };
	default:
		return { 0,0 };
	}
}

int XInputMoveComponent::GetLRTrgPower(Side LR)
{
	//�g���K�[�̓��͊��x
	switch (LR)
	{
	case Side::L:
		return static_cast<int>(_xinput.LeftTrigger);
	case Side::R:
		return static_cast<int>(_xinput.RightTrigger);
	default:
		return 0;
	}
}




