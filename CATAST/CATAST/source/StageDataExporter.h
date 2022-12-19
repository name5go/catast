/*****************************************************************//**
 * \file   StageDataExporter.h
 * \brief  �X�e�[�W����Json�ŏ����o���N���X
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "picojson/picojson.h"

class StageDataExporter
{
public:
	/**
	 * \brief �G�N�X�|�[�g
	 * \param �����o�����ƂȂ�I�u�W�F�N�g�T�[�o�[
	 * \param stageNumber �����o���t�@�C����
	 */
	void Export(ObjectServer&,int stageNumber);
};

