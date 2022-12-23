/*****************************************************************//**
 * \file   InputComponent.cpp
 * \brief  インプット情報、スティックからベクトルとradとか取得
 * 
 * \author めざし
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
	//xInput更新
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
	//コントローラーの傾き{x軸( -32768 ～ 32767 ),y軸( -32768 ～ 32767 )}を1000で割ってfloatで計算する用にいい感じにする
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
	//トリガーの入力感度
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




