/*****************************************************************//**
 * \file   DummySpike.cpp
 * \brief  仮一方向ギミック
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

void DummySpike::Init()
{
	_scale = { 0.1f,0.1f,0.1f };
	_name = "gimmick";
	auto handle = ModelServer::LoadModel("res/DummyTarget.mv1");
	MV1SetMaterialDifColor(handle, 0, GetColorF(1, 0, 0, 1));
	auto model = std::make_unique<MV1Component>(handle);
	AddComponent(std::move(model));
}

void DummySpike::Update(InputManager& input)
{
	ObjectBase::Update(input);
}

void DummySpike::Render()
{
	ObjectBase::Render();
	VECTOR forward{ VTransform({0.0f,0.0f,20.0f},_rotationMatrix) };
	DrawCone3D(VAdd(_position, forward), _position, 2.0f, 10, GetColor(255, 0, 0), GetColor(0, 0, 0), true);
}