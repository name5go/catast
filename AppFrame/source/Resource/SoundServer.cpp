/*****************************************************************//**
 * \file   SoundServer.cpp
 * \brief  �����̊Ǘ����s���N���X
 *
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/

#include "DxLib.h"
#include "SoundServer.h"

std::unordered_map<std::string, int> SoundServer::_mapBGM;
std::unordered_map<std::string, int> SoundServer::_mapSE;
std::unordered_map<std::string, int> SoundServer::_mapDefaultVolume;

void SoundServer::Init() {
	_mapBGM.clear();
}

void SoundServer::Release() {
	ClearSounds();
}

void SoundServer::ClearSounds() {
	for (auto&& graph : _mapBGM) {
		DeleteGraph(graph.second);
	}
	_mapBGM.clear();
}

int SoundServer::FindSE(std::string filename)
{
	auto itr = _mapSE.find(filename);
	if (itr != _mapSE.end()) {
		return itr->second;
	}
	return -1;
}

int SoundServer::EraseSE(std::string filename)
{
	auto itr = _mapSE.find(filename);
	if (itr != _mapSE.end()) {
		_mapSE.erase(itr);
		return 1;
	}
	return -1;
}

int SoundServer::LoadSE(std::string filename)
{
	int se = FindSE(filename);
	if (se == -1) {
		se = ::LoadSoundMem(filename.c_str());
		_mapSE[filename] = se;
		_mapDefaultVolume[filename] = GetVolumeSoundMem2(se);
	}
	return se;
}

int SoundServer::FindBGM(std::string filename)
{
	auto itr = _mapBGM.find(filename);
	if (itr != _mapBGM.end()) {
		return itr->second;
	}
	return -1;
}

int SoundServer::EraseBGM(std::string filename)
{
	auto itr = _mapBGM.find(filename);
	if (itr != _mapBGM.end()) {
		_mapBGM.erase(itr);
		return 1;
	}
	return -1;
}

int SoundServer::LoadBGM(std::string filename)
{
	int bgm = FindBGM(filename);
	if (bgm == -1) {
		bgm = ::LoadSoundMem(filename.c_str());
		_mapBGM[filename] = bgm;
		_mapDefaultVolume[filename] = GetVolumeSoundMem2(bgm);
	}
	return bgm;
}

void SoundServer::SetBGMVolume(float value)
{
	for (auto&& bgm : _mapBGM) {
		int nextVolume=_mapDefaultVolume[bgm.first] * value;
		ChangeVolumeSoundMem(nextVolume,bgm.second);
	}
}

void SoundServer::SetSEVolume(float value)
{
	for (auto&& se : _mapSE) {
		ChangeVolumeSoundMem(_mapDefaultVolume[se.first] * value, se.second);
	}
}
