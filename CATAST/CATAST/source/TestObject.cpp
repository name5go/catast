/*****************************************************************//**
 * \file   TestObject.cpp
 * \brief  �I�u�W�F�N�g�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/


//�ŏ��Ɉ�x���������I�ɌĂ΂��
void TestObject::Init()
{
	_scale={ 0.3f,0.3f,0.3f };
	//ModelServer���g����3D���f���̃n���h�����擾
	auto handle = ModelServer::LoadModel("res/character/SDChar.mv1");
	//3D���f��(MV1)�̕`��@�\������MV1Component��ǉ�����B
	auto mv1Component = std::make_unique<MV1Component>(handle);

	//�p���`��SE
	auto seFunc = [] {PlaySoundMem(SoundServer::LoadSE("res/character/Punch.mp3"), DX_PLAYTYPE_BACK);};
	//2�Ԃ̃A�j���[�V������11.7�b�Ɏd����
	mv1Component->AddAnimFunction(2, 11.7f, seFunc);
	//������SE
	auto seFunc2 = [] {PlaySoundMem(SoundServer::LoadSE("res/character/Walk.mp3"), DX_PLAYTYPE_BACK); };
	//1�Ԃ̃A�j���[�V������6.23�b�A25.9�b�Ɏd����
	mv1Component->AddAnimFunction(1, 6.23f, seFunc2);
	mv1Component->AddAnimFunction(1, 25.9f, seFunc2);

	mv1Component->SetAnimation(2);
	AddComponent(std::move(mv1Component));
	PlaySoundMem(SoundServer::LoadSE("res/character/Punch.mp3"), DX_PLAYTYPE_BACK);
}

void TestObject::Update(InputManager& input)
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Update���Ă�ł���B�܂�3D���f���̈ʒu��A�j���[�V�������X�V�����B
	ObjectBase::Update(input);

	//�L�[�{�[�h��A���������u�Ԃ�if�̒��ɓ���
	if (input.GetKeyA(InputState::Pressed)) {
		//MV1�R���|�[�l���g�ɃA�j���[�V�����Đ��@�\������̂ŃA�j���[�V������0�Ԃ��Đ�����悤�ɐݒ�
		GetComponent<MV1Component>()->SetAnimation(1);
	}

	//�L�[�{�[�h��A���������u�Ԃ�if�̒��ɓ���
	if (input.GetKeyS(InputState::Pressed)) {
		//MV1�R���|�[�l���g�ɃA�j���[�V�����Đ��@�\������̂ŃA�j���[�V������0�Ԃ��Đ�����悤�ɐݒ�
		GetComponent<MV1Component>()->SetAnimation(2);
	}

	//�L�[�{�[�h�̉E�������Ă����if�̒��ɓ���
	if (input.GetKeyRight(InputState::Hold)) {
		//X��������1.0������
		_position = VAdd(_position, { 1.0f,0.0f,0.0f });
	}
	//�L�[�{�[�h�̍��������Ă����if�̒��ɓ���
	else if (input.GetKeyLeft(InputState::Hold)) {
		//X��������-1.0������
		_position = VSub(_position, { 1.0f,0.0f,0.0f });
	}
}

void TestObject::Render()
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Render���Ă�ł���B�܂�3D���f�����`�悳���B
	ObjectBase::Render();

}
