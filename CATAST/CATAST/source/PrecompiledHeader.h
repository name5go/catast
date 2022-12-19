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

//ライブラリ
#include <sstream>
#include <functional>

//メイン
#include "ApplicationMain.h"

//ゲームモード
//--テンプレ
#include "ModeTest.h"
//--Modes
#include "ModeInGame.h"

//Editor
#include "ModeEditor.h"
#include "EditorButton.h"

//オブジェクト
//--テンプレ
#include "TestObject.h"
//--ステージ
#include "LevelBase.h"
//--プレイヤー
#include "Player.h"
#include "Camera.h"




