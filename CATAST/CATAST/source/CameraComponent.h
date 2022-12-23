#pragma once

//�J�������[�hFps�����J�����ATps0�v���C���[�̘��Վ��_�A�f�o�b�O�p�H�̃t���[�J����
/*
enum class CameraType
{
	Fps,
	Tps,
	FreeCamera
};*/

class CameraComponent :
    public ComponentBase
{
public:
	CameraComponent(float cameraDistance);
	~CameraComponent();
	void Update()override;
	void Render()override;
	void Debug()override;
	std::pair<VECTOR, VECTOR>GetCameraPosTarget() { return{ _cameraPosition,_cameraTarget }; }
	bool ChanegeAvaiavleCamera(bool available) { availableCam = available; return true; }

protected:
	//�J�������W�A�J�����^�[�Q�b�g�A�J�����Ɛe�Ƃ̋����x�N�g��
	VECTOR _cameraPosition, _cameraTarget,_cameraDistance;
	bool availableCam;
private:

};

