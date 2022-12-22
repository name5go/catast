/*****************************************************************//**
 * \file   Player.cpp
 * \brief  
 * 
 * \author �߂���
 * \date   December 2022
 *********************************************************************/

Player::Player()
{
	_scale = {0.01f, 0.01f, 0.01f};
	
}
Player::~Player()
{

}

void Player::Init()
{
	//ModelServer���g����3D���f���̃n���h�����擾
	auto handle = ModelServer::LoadModel("res/Player/Model/Player.mv1");
	//3D���f��(MV1)�̕`��@�\������MV1Component��ǉ�����B
	auto mv1Component = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(mv1Component));
	//camera�@�\����������
	float cameraDistance = 3.0;
	auto cameraComponent = std::make_unique<CameraComponent>(cameraDistance);
	AddComponent(std::move(cameraComponent));

	auto xinputComponent = std::make_unique<XInputComponent>();
	AddComponent(std::move(xinputComponent));

	_rotation = { 0.0f,Math::ToRadians(180.0f),0.0f};
}

void Player::Update(InputManager&input)
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Update���Ă�ł���B�܂�3D���f���̈ʒu��A�j���[�V�������X�V�����B
	ObjectBase::Update(input);

	std::pair<float,float> stick_L= GetComponent<XInputComponent>()->GetStickState(Stick::L);
	stick_L.first *= 0.1;

	VECTOR v;
	v =
	{ stick_L.first * static_cast<float>(std::cos(stick_L.second)),0.0f ,stick_L.first * static_cast<float>(std::sin(stick_L.second)) };
	if (input.GetPadL1(InputState::Hold))
	{
		v =
		{ stick_L.first * static_cast<float>(std::cos(stick_L.second)),stick_L.first * static_cast<float>(std::sin(stick_L.second)) ,0.0f };
	}

	float length_min = 0.02;
	if (stick_L.first > length_min)
	{
		_position = VAdd(_position, v);
	}

}

void Player::Render()
{
	//������_components�ɓo�^���Ă���R���|�[�l���g��Render���Ă�ł���B�܂�3D���f�����`�悳���B
	ObjectBase::Render();
}
