/*****************************************************************//**
 * \file   PreCompiled.h
 * \brief  プリコンパイルドヘッダー
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/
#pragma once

//AppFrame側のインクルード
#include"appframe.h"
#include"../../../AppFrame/source/Object/ComponentBase.h"

//標準ライブラリ
#include <sstream>
#include <functional>
#include <fstream>

//picojson
#include "picojson/picojson.h"

//メイン
#include "ApplicationMain.h"

//ゲームモード
//--テンプレ
#include "ModeTest.h"
//--Modes
#include "ModeInGame.h"
#include "ModeConfig.h"

//オブジェクト
//--テンプレ
#include "TestObject.h"
//--ステージ
#include "LevelBase.h"
//--プレイヤー
#include "Player.h"
#include "Camera.h"
//--デバッグ用
#include "XYZLine.h"
//--仮ギミックオブジェクト
#include "Dummy.h"
#include "DummyBlink.h"
#include "DummyBounce.h"
#include "DummySpike.h"
#include "DummyWarp.h"

//Editor
//--オブジェクト
#include "EditorButton.h"
#include "ObjectListWindow.h"
#include "EditorCamera.h"
#include "EditorSelectMarker.h"
#include "EditStageSelectWindow.h"
//--システム
#include "EditorUICreater.h"
#include "StageDataExporter.h"
#include "StageDataImporter.h"
