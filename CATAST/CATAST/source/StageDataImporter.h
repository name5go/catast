/*****************************************************************//**
 * \file   StageDataExporter.h
 * \brief  ステージ情報をJsonで読み込むクラス
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "picojson/picojson.h"
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
	 * \brief res/Stageフォルダ内のJsonファイルを読み込み、containerにデータを入れる関数
	 * \param stage 読み込むファイルの番号
	 * \param container 情報を入れるコンテナ
	 * \return 読み込み出来たらtrueを返す
	 */
	bool Import(int stage,std::vector<GimmickData>& container);
};
