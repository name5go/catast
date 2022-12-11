/*****************************************************************//**
 * \file   ImageServer.h
 * \brief  画像の読み込み、削除を行うクラスです。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "DxLib.h"
#include "ImageServer.h"

	std::unordered_map<std::string, int> ImageServer::_mapGraph;
	std::unordered_map<std::string, ImageServer::DIVGRAPH>	ImageServer::_mapDivGraph;

	void ImageServer::Init() {
		_mapGraph.clear();
	}

	void ImageServer::Release() {
		ClearGraph();
	}

	void ImageServer::ClearGraph() {
		for (auto&& graph : _mapGraph) {
			DeleteGraph(graph.second);
		}
		_mapGraph.clear();
	}

	int ImageServer::Find(std::string filename)
	{
		auto itr = _mapGraph.find(filename);
		if (itr != _mapGraph.end()) {
			return itr->second;
		}
		return -1;
	}

	int ImageServer::Erase(std::string filename)
	{
		auto itr = _mapGraph.find(filename);
		if (itr != _mapGraph.end()) {
			_mapGraph.erase(itr);
			return 1;
		}
		return -1;
	}

	int ImageServer::LoadGraph(std::string filename)
	{
		int cg = Find(filename);
		if (cg == -1) {
			cg = ::LoadGraph(filename.c_str());
			_mapGraph[filename] = cg;
		}
		return cg;
	}

	int	ImageServer::LoadDivGraph(const TCHAR* filename, int AllNum,
		int XNum, int YNum,
		int XSize, int YSize, int* HandleBuf)
	{
		// キーの検索
		auto itr = _mapDivGraph.find(filename);
		if (itr != _mapDivGraph.end())
		{
			// キーがあった
			// データをコピー
			for (int i = 0; i < itr->second.AllNum; i++) {
				HandleBuf[i] = itr->second.handle[i];
			}
			return 0;
		}
		// キーが無かった
		// まずはメモリを作成する
		int* hbuf = new int[AllNum];
		int err = ::LoadDivGraph(filename, AllNum, XNum, YNum, XSize, YSize, hbuf);     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する
		if (err == 0) {
			// 成功
			// キーとデータをmapに登録
			_mapDivGraph[filename].AllNum = AllNum;
			_mapDivGraph[filename].handle = hbuf;
			// データをコピー
			for (int i = 0; i < AllNum; i++) {
				HandleBuf[i] = hbuf[i];
			}
		}
		return err;
	}