// ピクセルシェーダーの入力
struct PS_INPUT
{
    float2 texCoords0 : TEXCOORD0; // テクスチャ座標
    float3 viewPos : TEXCOORD1; // 座標( ビュー空間 )
    float3 tan : TEXCOORD2; // 接線( ビュー空間 )
    float3 binorm : TEXCOORD3; // 従法線( ビュー空間 )
    float3 norm : TEXCOORD4; // 法線( ビュー空間 )
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
    float4 color0 : SV_TARGET0; // 出力カラー
};

// ===================================================================================================================
// DX ライブラリが用意している Constant Buffer
// ===================================================================================================================
struct DX_D3D11_CONST_MATERIAL
{
    float4 Diffuse; // ディフューズカラー
    float4 Specular; // スペキュラカラー
    float4 Ambient_Emissive; // マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー

    float Power; // スペキュラの強さ
    float TypeParam0; // マテリアルタイプパラメータ0
    float TypeParam1; // マテリアルタイプパラメータ1
    float TypeParam2; // マテリアルタイプパラメータ2
};

struct DX_D3D11_VS_CONST_FOG
{
    float LinearAdd; // フォグ用パラメータ end / ( end - start )
    float LinearDiv; // フォグ用パラメータ -1  / ( end - start )
    float Density; // フォグ用パラメータ density
    float E; // フォグ用パラメータ 自然対数の低

    float4 Color; // カラー
};

struct DX_D3D11_CONST_LIGHT
{
    int Type; // ライトタイプ( DX_LIGHTTYPE_POINT など )
    int3 Padding1; // パディング１

    float3 Position; // 座標( ビュー空間 )
    float RangePow2; // 有効距離の２乗

    float3 Direction; // 方向( ビュー空間 )
    float FallOff; // スポットライト用FallOff

    float3 Diffuse; // ディフューズカラー
    float SpotParam0; // スポットライト用パラメータ０( cos( Phi / 2.0f ) )

    float3 Specular; // スペキュラカラー
    float SpotParam1; // スポットライト用パラメータ１( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4 Ambient; // アンビエントカラーとマテリアルのアンビエントカラーを乗算したもの

    float Attenuation0; // 距離による減衰処理用パラメータ０
    float Attenuation1; // 距離による減衰処理用パラメータ１
    float Attenuation2; // 距離による減衰処理用パラメータ２
    float Padding2; // パディング２
};

struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[6]; // ライトパラメータ
    DX_D3D11_CONST_MATERIAL Material; // マテリアルパラメータ
    DX_D3D11_VS_CONST_FOG Fog; // フォグパラメータ
};

// 定数バッファピクセルシェーダー基本パラメータ
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
    float4 FactorColor; // アルファ値等

    float MulAlphaColor; // カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
    float AlphaTestRef; // アルファテストで使用する比較値
    float2 Padding1;

    int AlphaTestCmpMode; // アルファテスト比較モード( DX_CMP_NEVER など )
    int3 Padding2;

    float4 IgnoreTextureColor; // テクスチャカラー無視処理用カラー
};

cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    DX_D3D11_PS_CONST_BUFFER_BASE g_Base;
};

cbuffer cbD3D11_CONST_BUFFER_TIME : register(b2)
{
    //x 時間　y 輝度
    float4 param;
};
// ===================================================================================================================

SamplerState g_DiffuseMapSampler : register(s0); // ディフューズマップサンプラ
Texture2D g_DiffuseMapTexture : register(t0); // ディフューズマップテクスチャ

SamplerState g_NormalMapSampler : register(s1); // ノーマルマップサンプラ
Texture2D g_NormalMapTexture : register(t1); // ノーマルマップテクスチャ

SamplerState g_SpecularMapSampler : register(s2); // スぺキュラマップサンプラ
Texture2D g_SpecularMapTexture : register(t2); // スぺキュラマップテクスチャ


// float3 x float3[3]
float3 Multiply33(float3 v, float3 m0, float3 m1, float3 m2)
{
    float3 vec;

    vec.x = dot(v, m0);
    vec.y = dot(v, m1);
    vec.z = dot(v, m2);

    return vec;
}

PS_OUTPUT main(PS_INPUT PSInput)
{
    //ディフューズマップ：下地　スペキュラマップ：スライド　ノーマルマップ：FX
    //
    //int divCount = 32;
    int divCount = param.z;
	//移動量
    float offsetX = ceil(param.x) * (1.0 / divCount);

    PS_OUTPUT PSOutput;
	

    float centerX = 1.0f / divCount / 2.0f;
 
	//端のグリッド上でのXY座標
    float gridX = PSInput.texCoords0.x % (1.0f / divCount);
    float gridY = PSInput.texCoords0.y % (1.0f / divCount);
	//グリッド上の位置
    float gridPosX = ceil(PSInput.texCoords0.x / (1.0f / divCount));
    float gridPosY = ceil(PSInput.texCoords0.y / (1.0f / divCount));
	
    float4 baseDiffuse = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, float2((gridPosX - 0.5f) * (1.0f / divCount), (gridPosY - 0.5f) * (1.0f / divCount)));
    float4 moveDiffuse = g_SpecularMapTexture.Sample(g_DiffuseMapSampler, float2((gridPosX - 0.5f) * (1.0f / divCount) + offsetX, (gridPosY - 0.5f) * (1.0f / divCount)));
    float4 fxDiffuse = g_NormalMapTexture.Sample(g_DiffuseMapSampler, float2((gridPosX - 0.5f) * (1.0f / divCount), (gridPosY - 0.5f) * (1.0f / divCount)));
    float4 Diffuse = baseDiffuse * (1.0f-moveDiffuse.a) + moveDiffuse * (moveDiffuse.a);
    Diffuse = Diffuse * (1.0-fxDiffuse.a)+fxDiffuse * fxDiffuse.a;
    Diffuse.a = 1.0f;

	//ライト１個の半径
    float bigRadius = centerX * 0.9f;
	//ライト１個の内にある最も明るい部分の半径
    float smallRadius = centerX * 0.3f * max(Diffuse.x, max(Diffuse.y, Diffuse.z)) / 1.0;
    //バックカラー
    float4 backColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //中心からの距離の2乗
    float length =(gridX - centerX) * (gridX - centerX) + (gridY - centerX) * (gridY - centerX);
	
    //輝度補正
    float brightness = param.y;
    Diffuse = Diffuse * float4(brightness, brightness, brightness, 1.0f);
    
    
    if (length < bigRadius * bigRadius)
    {
        //中心からの距離に変換
        length = sqrt(length);
        PSOutput.color0 = Diffuse-(Diffuse - backColor) / bigRadius * (length - smallRadius);
    }
    else
    {
        PSOutput.color0 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    return PSOutput;
}