#include "ElectronicBoard.h"


ElectronicBoard::~ElectronicBoard()
{
}

void ElectronicBoard::Init()
{
    _name = "gimmick";
    auto handle = ModelServer::LoadModel("res/TestWall.mv1");
    auto mv1 = std::make_unique<MV1Component>(handle);
    AddComponent(std::move(mv1));

    //// シェーダーを有効にしたモデル描画
    //MV1SetUseOrigShader(TRUE);
    //// シェーダーを適応
    //_vHandle=LoadVertexShader("res/Shader/vertex_shader.vso");
    //_pHandle = LoadPixelShader("res/Shader/pixel_shader.pso");
    //_vHandle2 = LoadVertexShader("res/Shader/vertex_shader2.vso");
    //_pHandle2 = LoadPixelShader("res/Shader/pixel_shader2.pso");
    //
    //SetUseVertexShader(_vHandle2);
    //SetUsePixelShader(_pHandle2);
}

void ElectronicBoard::Update(InputManager& input)
{
    ObjectBase::Update(input);
}

void ElectronicBoard::Render()
{
    //SetUseVertexShader(_vHandle);
    //SetUsePixelShader(_pHandle);
    ObjectBase::Render();
    //SetUseVertexShader(_vHandle2);
    //SetUsePixelShader(_pHandle2);
}
