#pragma once

//カメラモードFps頭部カメラ、Tps0プレイヤーの俯瞰視点、デバッグ用？のフリーカメラ
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
	//カメラ座標、カメラターゲット、カメラと親との距離ベクトル
	VECTOR _cameraPosition, _cameraTarget,_cameraDistance;
	bool availableCam;
private:

};

