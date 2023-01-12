#include "SoundManager.h"
#include "../Resource/SoundServer.h"

SoundManager::SoundManager() :_bgmVolume{ 1.0f }, _seVolume{ 1.0f }
{
}

SoundManager::~SoundManager()
{
}

int SoundManager::PlaySE(int soundHandle, int playType, int topPositionFlag)
{
	int result = PlaySoundMem(soundHandle, playType, topPositionFlag);
	return result;
}

int SoundManager::PlayBGM(int soundHandle, int playType, int topPositionFlag)
{
	int result = PlaySoundMem(soundHandle, playType, topPositionFlag);
	return result;
}

void SoundManager::SetBGMVolume(float value)
{
	_bgmVolume = value;
	SoundServer::SetBGMVolume(_bgmVolume);
}

void SoundManager::SetSEVolume(float value)
{
	_seVolume = value;
	SoundServer::SetBGMVolume(_seVolume);
}
