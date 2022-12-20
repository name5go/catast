#include "ModeConfig.h"
/*****************************************************************//**
 * \file   ModeConfig.cpp
 * \brief  コンフィグ
 * 
 * \author めざし
 * \date   December 2022
 *********************************************************************/

bool ModeConfig::Initialize()
{
  return true;
}

bool ModeConfig::Terminate()
{
  ModeBase::Terminate();
  return true;
}

bool ModeConfig::Update(InputManager& input)
{
  ModeBase::Update(input);
  _objectServer->Update(input);

#if _DEBUG
  if (input.GetPadR1(InputState::Pressed)&& input.GetPadL1(InputState::Pressed) &&input.GetPadStart(InputState::Pressed))
  {
    EditorUICreater editorCreater;
    editorCreater.CreateUI(*_objectServer);
  }
#endif

  return true;
}

bool ModeConfig::Render()
{
  ModeBase::Render();

  _objectServer->Render();


  return true;
}

bool ModeConfig::Debug()
{
  ModeBase::Debug();
  _objectServer->Debug();
  return false;
}
