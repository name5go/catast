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
	 * \param stage �ǂݍ��ރX�e�[�W�̔ԍ�
	 * \param objectServer �ǂݍ��ރI�u�W�F�N�g�T�[�o�[
	 * \return �ǂݍ��ݏo������true��Ԃ�
	 */
	bool Import(int stage, ObjectServer& objectServer);
};
