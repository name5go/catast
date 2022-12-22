/*****************************************************************//**
 * \file   InputComponent.h
 * \brief  Xインプット情報を他クラス向けに計算。スティック入力の大きさ、角度。トリガーの入力感度を取得
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/
enum class Stick
{
	L,
	R
};

#pragma once
class XInputComponent :
    public ComponentBase
{
public:
	XInputComponent();
	~XInputComponent();
	bool Init()override;
	void Update()override;
	void Render()override;
	void Debug()override;
	//LR.first=length　LR.second=rad
	std::pair<float, float>GetStickState(Stick LR) { return GetStickLenRad(LR); }

protected:

private:
	XINPUT_STATE _xinput;//XINPUTで取得した値を格納、Input内部で更新
	std::pair<float, float>GetStickLenRad(Stick LR);
	//スティック入力方向への傾きの大きさ
	float _stickTilt_Length_R;
	float _stickTilt_Length_L;
	//スティック入力方向へのラディアン
	float _stickTilt_Rad_R;
	float _stickTilt_Rad_L;
	//R2、L2トリガーの入力の大きさ
	int _trg_R2;
	int _trg_L2;
};

