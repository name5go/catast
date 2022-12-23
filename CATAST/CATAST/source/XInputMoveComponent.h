/*****************************************************************//**
 * \file   InputComponent.h
 * \brief  Xインプット情報を他クラス向けに計算。スティック入力の大きさ、角度。トリガーの入力感度を取得
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/
enum class Side
{
	L,
	R
};

enum class MoveType
{
	As_3D,
	As_2D,
	None
};

enum class CameraType
{
	FPS,
	TPS,
	FREE_CAMERA,
	NO_MOVE
};

#pragma once
class XInputMoveComponent :
    public ComponentBase
{
public://std::pair<float,int> MovePowerAndType
	XInputMoveComponent(float power,MoveType mov,CameraType cam);
	~XInputMoveComponent();

	bool Init()override;
	void Update()override;
	void Render()override;
	void Debug()override;

	//アクター制御
	inline void ActorMove();
	inline void CameraMove();

	bool ChangeCameraType(CameraType cam) { _cam = cam; return true; }
	bool ChangeMoveType(MoveType mov) { _mov = mov; return true; }

	//スティックの入力方向と感度を取得。LR.first=length　LR.second=rad
	std::pair<float, float>GetStickState(Side LR) { return GetStickLenRad(LR); }
	//トリガーの感度を取得
	int GetTrgPower(Side LR) { return GetLRTrgPower(LR); }

protected:

private:
	//動く際の力の大きさとどう動くか
	float _movePower;
	MoveType _mov;
	CameraType _cam;

	XINPUT_STATE _xinput;//XINPUTで取得した値を格納、Input内部で更新
	std::pair<float, float>GetStickLenRad(Side LR);
	int GetLRTrgPower(Side LR);
};

