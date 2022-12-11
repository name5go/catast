/*****************************************************************//**
 * \file   ModelServer.h
 * \brief  3Dモデルの読み込み、削除を行うクラスです。
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <tchar.h>

	class ModelServer {
	public:
		static void Init();//<_mapGraphの初期化
		static void Release();//<ClearGraph呼び出し

		static void ClearModel();//<_mapGraphデータの全削除

		/**
		 * \brief _mapGraphのキー検索
		 *
		 * \param filename 検索するキー名
		 * \return キーに対応した値を返す
		 */
		static int Find(std::string filename);
		static int Erase(std::string filename);
		/**
		 * \brief 読み込み済のファイル出なければmapに登録
		 *
		 * \param filename 読み込むファイル名
		 * \return 読み込んだ値、読み込み済みなら-1を返す
		 */
		static int LoadModel(std::string filename);

	private:
		static std::unordered_map<std::string, int> _mapGraph;
	};
