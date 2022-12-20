/*****************************************************************//**
 * \file   ModeTest.cpp
 * \brief  ���[�h�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/


 //�ŏ��Ɉ�x���������I�ɌĂ΂��
bool ModeTest::Initialize() {
	if (!ModeBase::Initialize()) { return false; }
	////�e�X�g�I�u�W�F�N�g�̒ǉ�
	//_objectServer->Add(std::make_unique<TestObject>());
	
	//editor���Ăڏo�����߂̋@�\
	EditorUICreater editorCreater;
	editorCreater.CreateUI(*_objectServer);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	//�J�����̃Z�b�g
	SetCameraPositionAndTarget_UpVecY({ 0.0f,50.0f,-150.0f }, { 0.0f,50.0f,0.0f });
	//���C�g�̐ݒ�
	//ChangeLightTypeDir({ 0.1f,1.0f,0.5f });
	SetLightDifColor({2.0f, 2.0f, 2.0f, 0.0f});
	return true;
}

//�폜���鎞�Ɉ�x���������I�ɌĂ΂��
bool ModeTest::Terminate() {
	ModeBase::Terminate();
	return true;

}

bool ModeTest::Update(InputManager& input) {
	ModeBase::Update(input);
	_objectServer->Update(input);

	return true;
}

bool ModeTest::Render() {
	ModeBase::Render();

	_objectServer->Render();


	return true;
}

bool ModeTest::Debug()
{
	ModeBase::Debug();
	_objectServer->Debug();
	return false;
}

