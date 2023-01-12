/*****************************************************************//**
 * \file   SoundServer.h
 * \brief  �����̊Ǘ����s���N���X
 * 
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <tchar.h>
class SoundServer {
public:
	static void Init();//<_mapGraph�̏�����
	static void Release();//<ClearGraph�Ăяo��

	static void ClearSounds();//<_mapGraph�f�[�^�̑S�폜

	/**
	 * \brief _mapGraph�̃L�[����
	 *
	 * \param filename ��������L�[��
	 * \return �L�[�ɑΉ������l��Ԃ�
	 */
	static int FindBGM(std::string filename);
	static int EraseBGM(std::string filename);
	/**
	 * \brief �ǂݍ��ݍς̃t�@�C���o�Ȃ����map�ɓo�^
	 *
	 * \param filename �ǂݍ��ރt�@�C����
	 * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
	 */
	static int LoadBGM(std::string filename);

	/**
 * \brief _mapGraph�̃L�[����
 *
 * \param filename ��������L�[��
 * \return �L�[�ɑΉ������l��Ԃ�
 */
	static int FindSE(std::string filename);
	static int EraseSE(std::string filename);
	/**
	 * \brief �ǂݍ��ݍς̃t�@�C���o�Ȃ����map�ɓo�^
	 *
	 * \param filename �ǂݍ��ރt�@�C����
	 * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
	 */
	static int LoadSE(std::string filename);

	static void SetBGMVolume(float volume);
	static void SetSEVolume(float volume);

private:
	static std::unordered_map<std::string, int> _mapBGM;
	static std::unordered_map<std::string, int> _mapSE;
	static std::unordered_map<std::string, int> _mapDefaultVolume;
};
