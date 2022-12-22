/*****************************************************************//**
 * \file   PreCompiled.h
 * \brief  �v���R���p�C���h�w�b�_�[
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/
#pragma once

//AppFrame���̃C���N���[�h
#include"appframe.h"
#include"../../../AppFrame/source/Object/ComponentBase.h"

//�W�����C�u����
#include <sstream>
#include <functional>
#include <fstream>
#include <math.h>

//picojson
#include "picojson/picojson.h"

//���C��
#include "ApplicationMain.h"
//--�v�Z�p
#include"Math.h"

//�Q�[�����[�h
//--�e���v��
#include "ModeTest.h"
//--Modes
#include "ModeInGame.h"
#include "ModeConfig.h"

//Game.sln���ɍ�����R���|�[�l���g
//--�J����
#include"CameraComponent.h"
//--�C���v�b�g
#include"XInputComponent.h"

//�I�u�W�F�N�g
//--�e���v��
#include "TestObject.h"
//--�X�e�[�W
#include "LevelBase.h"
//--�v���C���[
#include "Player.h"
//--�J����
#include "Camera.h"
//--�f�o�b�O�p
#include "XYZLine.h"
//--���M�~�b�N�I�u�W�F�N�g
#include "Dummy.h"
#include "DummyBlink.h"
#include "DummyBounce.h"
#include "DummySpike.h"
#include "DummyWarp.h"

//Editor
//--�I�u�W�F�N�g
#include "EditorButton.h"
#include "ObjectListWindow.h"
#include "EditorCamera.h"
#include "EditorSelectMarker.h"
#include "EditStageSelectWindow.h"
//--�V�X�e��
#include "EditorUICreater.h"
#include "StageDataExporter.h"
#include "StageDataImporter.h"
