/*****************************************************************//**
 * \file   FontServer.h
 * \brief  フォントの読み込みを行うクラス
 * 
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <unordered_map>
class FontServer
{
public:
	static void Init();//<_fontGraphの初期化
	static void Release();//<ClearFont呼び出し

	static void ClearFont();//<_fontGraphデータの全削除

	/**
	 * \brief _fontGraphのキー検索
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
	static int LoadFont(std::string filename);

private:
	static std::unordered_map<std::string, int> _fontGraph;
};

