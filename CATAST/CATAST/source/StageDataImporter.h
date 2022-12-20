/*****************************************************************//**
 * \file   StageDataExporter.h
 * \brief  �X�e�[�W����Json�œǂݍ��ރN���X
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once

class StageDataImporter
{
public:
	struct GimmickData {
		int Type;
		VECTOR Position;
		VECTOR Rotation;
		VECTOR Scale;
	};

	/**
	 * \brief res/Stage�t�H���_����Json�t�@�C����ǂݍ��݁Acontainer�Ƀf�[�^������֐�
	 * \param stage �ǂݍ��ރt�@�C���̔ԍ�
	 * \param container ��������R���e�i
	 * \return �ǂݍ��ݏo������true��Ԃ�
	 */
	bool Import(int stage,std::vector<GimmickData>& container);
};
