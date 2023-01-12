/*****************************************************************//**
 * \file   SoundServer.h
 * \brief  音声の管理を行うクラス
 * 
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <tchar.h>
class SoundServer {
public:
	static void Init();//<_mapGraphの初期化
	static void Release();//<ClearGraph呼び出し

	static void ClearSounds();//<_mapGraphデータの全削除

	/**
	 * \brief _mapGraphのキー検索
	 *
	 * \param filename 検索するキー名
	 * \return キーに対応した値を返す
	 */
	static int FindBGM(std::string filename);
	static int EraseBGM(std::string filename);
	/**
	 * \brief 読み込み済のファイル出なければmapに登録
	 *
	 * \param filename 読み込むファイル名
	 * \return 読み込んだ値、読み込み済みなら-1を返す
	 */
	static int LoadBGM(std::string filename);

	/**
 * \brief _mapGraphのキー検索
 *
 * \param filename 検索するキー名
 * \return キーに対応した値を返す
 */
	static int FindSE(std::string filename);
	static int EraseSE(std::string filename);
	/**
	 * \brief 読み込み済のファイル出なければmapに登録
	 *
	 * \param filename 読み込むファイル名
	 * \return 読み込んだ値、読み込み済みなら-1を返す
	 */
	static int LoadSE(std::string filename);

	static void SetBGMVolume(float volume);
	static void SetSEVolume(float volume);
	static float GetBGMVolume() { return _bgmVolume; }
	static float GetSEVolume() { return _seVolume; }
private:
	static std::unordered_map<std::string, int> _mapBGM;
	static std::unordered_map<std::string, int> _mapSE;
	static std::unordered_map<std::string, int> _mapDefaultVolume;
	static float _bgmVolume;
	static float _seVolume;
};
