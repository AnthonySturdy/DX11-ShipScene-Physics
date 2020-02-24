//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txSpecular : register(t2);
SamplerState samLinear : register(s0);

struct SurfaceInfo
{
	float4 AmbientMtrl;
	float4 DiffuseMtrl;
	float4 SpecularMtrl;
};

struct Light
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float SpecularPower;
	float3 LightVecW;
};

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;

	SurfaceInfo surface;
	Light light;

	float3 EyePosW;
	float gTime;
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : NORMAL0;
	float3 eyePos : POSITION0;
	float2 Tex : TEXCOORD0;
	float3 vPos : POSITION1;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( float4 Pos : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD0 )
{
    PS_INPUT output = (PS_INPUT)0;

	output.Tex = Tex;

    output.Pos = mul( Pos, World );

	//Compute vector from the vertex to eye position
	//output.Pos is currently the position in world space
	float3 toEye = normalize(EyePosW - output.Pos.xyz);
	output.eyePos = toEye;

	//Make vertices wobble when under water (Water depth is -1, but do it after -5)
	if (Pos.y < -4) {
		output.Pos.x = output.Pos.x + (sin(gTime + Pos.z * 1.8f) * 0.7f);
		output.Pos.z = output.Pos.z + (sin(gTime + Pos.y * 1.4f) * 0.7f);
	}

	output.vPos = output.Pos;

    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
	
	// Convert from local space to world space
	// W component of vector is 0 as vectors cannot be translated
	float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
	output.Norm = normalW;

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader - Specular lighting
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float3 normalW = normalize(input.Norm);

	float3 toEye = normalize(EyePosW - input.eyePos);

	// Get texture data from file
	float4 textureColour = txDiffuse.Sample(samLinear, input.Tex);

	//Discard pixel if alpha is low
	clip(textureColour.a - 0.15f);

	float3 ambient = float3(0.0f, 0.0f, 0.0f);
	float3 diffuse = float3(0.0f, 0.0f, 0.0f);
	float3 specular = float3(0.0f, 0.0f, 0.0f);

	float3 lightLecNorm = normalize(light.LightVecW);
	// Compute Colour

	// Compute the reflection vector.
	float3 r = reflect(-lightLecNorm, normalW);

	// Determine how much specular light makes it into the eye.
	float specularAmount = pow(max(dot(r, toEye), 0.0f), light.SpecularPower);

	// Determine the diffuse light intensity that strikes the vertex.
	float diffuseAmount = max(dot(lightLecNorm, normalW), 0.0f);

	// Only display specular when there is diffuse
	if (diffuseAmount <= 0.0f)
	{
		specularAmount = 0.0f;
	}

	// Compute the ambient, diffuse, and specular terms separately.
	specular += specularAmount * (surface.SpecularMtrl * light.SpecularLight).rgb;
	diffuse += diffuseAmount * (surface.DiffuseMtrl * light.DiffuseLight).rgb;
	ambient += (surface.AmbientMtrl * light.AmbientLight).rgb;

	// Sum all the terms together and copy over the diffuse alpha.
	float4 finalColour;
	finalColour.rgb = (textureColour.rgb * (ambient + diffuse)) + specular;
	finalColour.a = surface.DiffuseMtrl.a;

	//If below sea level, turning colour more blue
	float4 waterCol = float4(0.0f, 0.031f, 0.201f, 1.0f);
	float4 waterDeepCol = float4(0.0f, 0.0f, 0.05f, 1.0f);
	if (input.vPos.y < 0) {
		finalColour = lerp(finalColour, waterCol, saturate(abs(input.vPos.y / 9.0f)));
		finalColour = lerp(finalColour, waterDeepCol, saturate(abs(input.vPos.y / 20.0f)));
	} 

	return finalColour;
}