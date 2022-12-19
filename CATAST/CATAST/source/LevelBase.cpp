/*****************************************************************//**
 * \file   LevelBase.cpp
 * \brief  
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/


void LevelBase::Init()
{
	//ModelServer���g����3D���f���̃n���h�����擾
	auto handle = ModelServer::LoadModel("res/LevelModel/LevelBase.mv1");
	//3D���f��(MV1)�̕`��@�\������MV1Component��ǉ�����B
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
}

void LevelBase::Update(InputManager&input)
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Update���Ă�ł���B�܂�3D���f���̈ʒu��A�j���[�V�������X�V�����B
	ObjectBase::Update(input);
}

void LevelBase::Render()
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Render���Ă�ł���B�܂�3D���f�����`�悳���B
	ObjectBase::Render();

}
