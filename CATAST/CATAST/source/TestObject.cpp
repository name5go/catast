/*****************************************************************//**
 * \file   TestObject.cpp
 * \brief  �I�u�W�F�N�g�̎�����ł��B�Q�[�����ł͎g�p���Ȃ��B
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/

#include "PrecompiledHeader.h"
#include "TestObject.h"



//�ŏ��Ɉ�x���������I�ɌĂ΂��
void TestObject::Init()
{
	//ModelServer���g����3D���f���̃n���h�����擾
	auto handle = ModelServer::LoadModel("res/ridgidSimTest.mv1");
	//3D���f��(MV1)�̕`��@�\������MV1Component��ǉ�����B
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void TestObject::Update(InputManager& input)
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Update���Ă�ł���B�܂�3D���f���̈ʒu��A�j���[�V�������X�V�����B
	ObjectBase::Update(input);

	//�L�[�{�[�h��A���������u�Ԃ�if�̒��ɓ���
	if (input.GetKeyA(InputState::Pressed)) {
		//MV1�R���|�[�l���g�ɃA�j���[�V�����Đ��@�\������̂ŃA�j���[�V������0�Ԃ��Đ�����悤�ɐݒ�
		GetComponent<MV1Component>()->SetAnimation(0);
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

	std::stringstream ss;
	ss << "���E�L�[�ňړ��@A�L�[�ŃA�j���[�V�����Đ�";
	DrawString(0, 0, ss.str().c_str(), GetColor(255, 255, 255));
}
