/*****************************************************************//**
 * \file   FontServer.h
 * \brief  �t�H���g�̓ǂݍ��݂��s���N���X
 * 
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <unordered_map>
class FontServer
{
public:
	static void Init();//<_fontGraph�̏�����
	static void Release();//<ClearFont�Ăяo��

	static void ClearFont();//<_fontGraph�f�[�^�̑S�폜

	/**
	 * \brief _fontGraph�̃L�[����
	 *
	 * \param filename ��������L�[��
	 * \return �L�[�ɑΉ������l��Ԃ�
	 */
	static int Find(std::string filename);
	static int Erase(std::string filename);
	/**
	 * \brief �ǂݍ��ݍς̃t�@�C���o�Ȃ����map�ɓo�^
	 *
	 * \param filename �ǂݍ��ރt�@�C����
	 * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
	 */
	static int LoadFont(std::string filename);

private:
	static std::unordered_map<std::string, int> _fontGraph;
};

