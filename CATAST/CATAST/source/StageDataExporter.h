/*****************************************************************//**
 * \file   StageDataExporter.h
 * \brief  ステージ情報をJsonで書き出すクラス
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "picojson/picojson.h"

class StageDataExporter
{
public:
	/**
	 * \brief エクスポート
	 * \param 書き出し元となるオブジェクトサーバー
	 * \param stageNumber 書き出すファイル名
	 */
	void Export(ObjectServer&,int stageNumber);
};

