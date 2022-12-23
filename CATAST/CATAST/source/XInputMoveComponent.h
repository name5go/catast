/*****************************************************************//**
 * \file   InputComponent.h
 * \brief  X�C���v�b�g���𑼃N���X�����Ɍv�Z�B�X�e�B�b�N���͂̑傫���A�p�x�B�g���K�[�̓��͊��x���擾
 * 
 * \author �߂���
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

	//�A�N�^�[����
	inline void ActorMove();
	inline void CameraMove();

	bool ChangeCameraType(CameraType cam) { _cam = cam; return true; }
	bool ChangeMoveType(MoveType mov) { _mov = mov; return true; }

	//�X�e�B�b�N�̓��͕����Ɗ��x���擾�BLR.first=length�@LR.second=rad
	std::pair<float, float>GetStickState(Side LR) { return GetStickLenRad(LR); }
	//�g���K�[�̊��x���擾
	int GetTrgPower(Side LR) { return GetLRTrgPower(LR); }

protected:

private:
	//�����ۂ̗͂̑傫���Ƃǂ�������
	float _movePower;
	MoveType _mov;
	CameraType _cam;

	XINPUT_STATE _xinput;//XINPUT�Ŏ擾�����l���i�[�AInput�����ōX�V
	std::pair<float, float>GetStickLenRad(Side LR);
	int GetLRTrgPower(Side LR);
};

