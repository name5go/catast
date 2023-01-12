#pragma once
#include <DxLib.h>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	int PlaySE(int soundHandle,int playType,int topPositionFlag=true);
	int PlayBGM(int soundHandle, int playType, int topPositionFlag = true);

	void SetBGMVolume(float value);
	void SetSEVolume(float value);
	float GetBGMVolume() { return _bgmVolume; }
	float GetSEVolume() { return _seVolume; }
private:
	float _bgmVolume;
	float _seVolume;
};