/*****************************************************************//**
 * \file   ImageServer.h
 * \brief  �摜�̓ǂݍ��݁A�폜���s���N���X�ł��B
 *
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <tchar.h>
	class ImageServer {
	public:
		static void Init();//<_mapGraph�̏�����
		static void Release();//<ClearGraph�Ăяo��

		static void ClearGraph();//<_mapGraph�f�[�^�̑S�폜

		/**
		 * \brief _mapGraph�̃L�[����
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
		static int LoadGraph(std::string filename);
		static int LoadDivGraph(const TCHAR* filename, int allnum, int xnum, int ynum, int xsize, int ysize, int* handlebuff);

	private:
		static std::unordered_map<std::string, int> _mapGraph;
		typedef struct {
			int AllNum;
			int* handle;
		}DIVGRAPH;
		static std::unordered_map<std::string, DIVGRAPH> _mapDivGraph;
	};
