/*****************************************************************//**
 * \file   ModeInGame.cpp
 * \brief  �C���Q�[�������ł�
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/


bool ModeInGame::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	//�I�u�W�F�N�g�̒ǉ�
	_objectServer->Add(std::make_unique<LevelBase>());


	EditorUICreater editor;
	editor.CreateUI(*_objectServer);

	_objectServer->Add(std::make_unique<MessageWindow>());
	//�J�����̃Z�b�g
	SetCameraPositionAndTarget_UpVecY({ 0.0f,50.0f,-150.0f }, { 0.0f,50.0f,0.0f });
	//���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
	SetLightDifColor({ 2.0f, 2.0f, 2.0f, 0.0f });
	return false;
}

bool ModeInGame::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeInGame::Update(InputManager& input)
{
	ModeBase::Update(input);
	_objectServer->Update(input);

	return false;
}

bool ModeInGame::Render()
{
	ModeBase::Render();

	_objectServer->Render();
	return false;
}

bool ModeInGame::Debug()
{
	ModeBase::Debug();
	_objectServer->Debug();
	return false;
}
