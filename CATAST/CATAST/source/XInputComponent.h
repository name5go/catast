/*****************************************************************//**
 * \file   InputComponent.h
 * \brief  X�C���v�b�g���𑼃N���X�����Ɍv�Z�B�X�e�B�b�N���͂̑傫���A�p�x�B�g���K�[�̓��͊��x���擾
 * 
 * \author �߂���
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
	//LR.first=length�@LR.second=rad
	std::pair<float, float>GetStickState(Stick LR) { return GetStickLenRad(LR); }

protected:

private:
	XINPUT_STATE _xinput;//XINPUT�Ŏ擾�����l���i�[�AInput�����ōX�V
	std::pair<float, float>GetStickLenRad(Stick LR);
	//�X�e�B�b�N���͕����ւ̌X���̑傫��
	float _stickTilt_Length_R;
	float _stickTilt_Length_L;
	//�X�e�B�b�N���͕����ւ̃��f�B�A��
	float _stickTilt_Rad_R;
	float _stickTilt_Rad_L;
	//R2�AL2�g���K�[�̓��͂̑傫��
	int _trg_R2;
	int _trg_L2;
};

