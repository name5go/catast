/*****************************************************************//**
 * \file   ImageServer.h
 * \brief  画像の読み込み、削除を行うクラスです。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <tchar.h>
	class ImageServer {
	public:
		static void Init();//<_mapGraphの初期化
		static void Release();//<ClearGraph呼び出し

		static void ClearGraph();//<_mapGraphデータの全削除

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
