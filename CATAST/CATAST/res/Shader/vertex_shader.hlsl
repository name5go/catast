// 頂点シェーダーの入力
// モデルの頂点情報を合わないと不正な値が入るので注意
struct VS_INPUT {
	float3 pos        : POSITION;  // 座標( ローカル空間 )
	float3 norm       : NORMAL0;   // 法線( ローカル空間 )
	float4 diff       : COLOR0;    // ディフューズカラー
	float4 spe        : COLOR1;    // スペキュラカラー
	float2 texCoords0 : TEXCOORD0; // テクスチャ座標
	float3 tan        : TANGENT0;  // 接線( ローカル空間 )
};

// 頂点シェーダーの出力
struct VS_OUTPUT {
	float2 texCoords0 : TEXCOORD0;   // テクスチャ座標
	float3 viewPos    : TEXCOORD1;   // 座標( ビュー空間 )
	float3 tan        : TEXCOORD2;   // 接線( ビュー空間 )
	float3 binorm     : TEXCOORD3;   // 従法線( ビュー空間 )
	float3 norm       : TEXCOORD4;   // 法線( ビュー空間 )
	float4 pos        : SV_POSITION; // 座標( プロジェクション空間 )
};

// ===================================================================================================================
// DX ライブラリが用意している Constant Buffer
// ===================================================================================================================
// 基本パラメータ
struct DX_D3D11_VS_CONST_BUFFER_BASE {
	float4 AntiViewportMatrix[4]; // アンチビューポート行列
	float4 ProjectionMatrix[4];   // ビュー　→　プロジェクション行列
	float4 ViewMatrix[3];         // ワールド　→　ビュー行列
	float4 LocalWorldMatrix[3];   // ローカル　→　ワールド行列
	float4 ToonOutLineSize;       // トゥーンの輪郭線の大きさ
	float DiffuseSource;          // ディフューズカラー( 0.0f:マテリアル  1.0f:頂点 )
	float SpecularSource;         // スペキュラカラー(   0.0f:マテリアル  1.0f:頂点 )
	float MulSpecularColor;       // スペキュラカラー値に乗算する値( スペキュラ無効処理で使用 )
	float Padding;
};

// その他の行列
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX {
	float4 ShadowMapLightViewProjectionMatrix[3][4]; // シャドウマップ用のライトビュー行列とライト射影行列を乗算したもの
	float4 TextureMatrix[3][2];                      // テクスチャ座標操作用行列
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_VS_BASE : register(b1) {
	DX_D3D11_VS_CONST_BUFFER_BASE g_Base;
};

// その他の行列
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX : register(b2) {
	DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX g_OtherMatrix;
};
// ===================================================================================================================

// float3 -> float4
float4 Convert34(float3 v) {
	float4 vec;

	vec.xyz = v;
	vec.w = 1.0f;

	return vec;
}

// float4 x float4[3]
float4 Multiply43(float4 v, float4 m0, float4 m1, float4 m2) {
	float4 vec;

	vec.x = dot(v, m0);
    vec.y = dot(v, m1);
    vec.z = dot(v, m2);
    vec.w = 1.0f;

	return vec;
}

// float4 x float4[4]
float4 Multiply44(float4 v, float4 m0, float4 m1, float4 m2, float4 m3) {
	float4 vec;

	vec.x = dot(v, m0);
    vec.y = dot(v, m1);
    vec.z = dot(v, m2);
    vec.w = dot(v, m3);

	return vec;
}

// float3 x float3[3]
float3 Multiply33(float3 v, float3 m0, float3 m1, float3 m2) {
	float3 vec;

	vec.x = dot(v, m0);
    vec.y = dot(v, m1);
    vec.z = dot(v, m2);

	return vec;
}

// main関数
VS_OUTPUT main(VS_INPUT VSInput) {
	// モデルの頂点をビュー変換させる
    float4 lLocalPosition = Convert34(VSInput.pos);
	float4 lWorldPosition = Multiply43(lLocalPosition, g_Base.LocalWorldMatrix[0], g_Base.LocalWorldMatrix[1], g_Base.LocalWorldMatrix[2]);
	float4 lViewPosition = Multiply43(lWorldPosition, g_Base.ViewMatrix[0], g_Base.ViewMatrix[1], g_Base.ViewMatrix[2]);
	// モデルの法線と接線と従法線をビュー空間へ変換する(従法線は法線と接線から外積で作る)
	float3 lwMat0 = g_Base.LocalWorldMatrix[0].xyz;
	float3 lwMat1 = g_Base.LocalWorldMatrix[1].xyz;
	float3 lwMat2 = g_Base.LocalWorldMatrix[2].xyz;
	float3 lWorldTan = Multiply33(VSInput.tan, lwMat0, lwMat1, lwMat2);
	float3 binorm = cross(VSInput.norm, VSInput.tan);
	float3 lWorldBin = Multiply33(binorm, lwMat0, lwMat1, lwMat2);
	float3 lWorldNrm = Multiply33(VSInput.norm, lwMat0, lwMat1, lwMat2);
	float3 vMat0 = g_Base.ViewMatrix[0].xyz;
	float3 vMat1 = g_Base.ViewMatrix[1].xyz;
	float3 vMat2 = g_Base.ViewMatrix[2].xyz;
	float3 lViewTan = Multiply33(lWorldTan, vMat0, vMat1, vMat2);
	float3 lViewBin = Multiply33(lWorldBin, vMat0, vMat1, vMat2);
	float3 lViewNrm = Multiply33(lWorldNrm, vMat0, vMat1, vMat2);

	VS_OUTPUT VSOutput;

	// テクスチャ座標変換行列による変換を行った結果のテクスチャ座標をセット
	VSOutput.texCoords0.x = dot(VSInput.texCoords0, g_OtherMatrix.TextureMatrix[0][0]);
	VSOutput.texCoords0.y = dot(VSInput.texCoords0, g_OtherMatrix.TextureMatrix[0][1]);
	VSOutput.viewPos = lViewPosition.xyz;
	VSOutput.tan = lViewTan;
	VSOutput.binorm = lViewBin;
	VSOutput.norm = lViewNrm;
	// ビュー空間の座標に透視変換を適応
	VSOutput.pos = Multiply44(lViewPosition, g_Base.ProjectionMatrix[0], g_Base.ProjectionMatrix[1], g_Base.ProjectionMatrix[2], g_Base.ProjectionMatrix[3]);

    return VSOutput;
}