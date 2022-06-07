// Basic Texture Shader

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;
layout(location = 5) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 Colour;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) out VertexOutput Output;
layout (location = 4) out flat int v_EntityID;

void main()
{
	Output.Colour = a_Colour;
	Output.TexCoord = a_TexCoord;
	Output.TexIndex = a_TexIndex;
	Output.TilingFactor = a_TilingFactor;
	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 colour;
layout(location = 1) out int colour2;

struct VertexOutput
{
	vec4 Colour;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) in VertexOutput Input;
layout (location = 4) in flat int v_EntityID;

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	vec4 texColour = Input.Colour;
	switch(int(Input.TexIndex))
	{
		case  0: texColour *= texture(u_Textures[ 0], Input.TexCoord * Input.TilingFactor); break;
		case  1: texColour *= texture(u_Textures[ 1], Input.TexCoord * Input.TilingFactor); break;
		case  2: texColour *= texture(u_Textures[ 2], Input.TexCoord * Input.TilingFactor); break;
		case  3: texColour *= texture(u_Textures[ 3], Input.TexCoord * Input.TilingFactor); break;
		case  4: texColour *= texture(u_Textures[ 4], Input.TexCoord * Input.TilingFactor); break;
		case  5: texColour *= texture(u_Textures[ 5], Input.TexCoord * Input.TilingFactor); break;
		case  6: texColour *= texture(u_Textures[ 6], Input.TexCoord * Input.TilingFactor); break;
		case  7: texColour *= texture(u_Textures[ 7], Input.TexCoord * Input.TilingFactor); break;
		case  8: texColour *= texture(u_Textures[ 8], Input.TexCoord * Input.TilingFactor); break;
		case  9: texColour *= texture(u_Textures[ 9], Input.TexCoord * Input.TilingFactor); break;
		case 10: texColour *= texture(u_Textures[10], Input.TexCoord * Input.TilingFactor); break;
		case 11: texColour *= texture(u_Textures[11], Input.TexCoord * Input.TilingFactor); break;
		case 12: texColour *= texture(u_Textures[12], Input.TexCoord * Input.TilingFactor); break;
		case 13: texColour *= texture(u_Textures[13], Input.TexCoord * Input.TilingFactor); break;
		case 14: texColour *= texture(u_Textures[14], Input.TexCoord * Input.TilingFactor); break;
		case 15: texColour *= texture(u_Textures[15], Input.TexCoord * Input.TilingFactor); break;
		case 16: texColour *= texture(u_Textures[16], Input.TexCoord * Input.TilingFactor); break;
		case 17: texColour *= texture(u_Textures[17], Input.TexCoord * Input.TilingFactor); break;
		case 18: texColour *= texture(u_Textures[18], Input.TexCoord * Input.TilingFactor); break;
		case 19: texColour *= texture(u_Textures[19], Input.TexCoord * Input.TilingFactor); break;
		case 20: texColour *= texture(u_Textures[20], Input.TexCoord * Input.TilingFactor); break;
		case 21: texColour *= texture(u_Textures[21], Input.TexCoord * Input.TilingFactor); break;
		case 22: texColour *= texture(u_Textures[22], Input.TexCoord * Input.TilingFactor); break;
		case 23: texColour *= texture(u_Textures[23], Input.TexCoord * Input.TilingFactor); break;
		case 24: texColour *= texture(u_Textures[24], Input.TexCoord * Input.TilingFactor); break;
		case 25: texColour *= texture(u_Textures[25], Input.TexCoord * Input.TilingFactor); break;
		case 26: texColour *= texture(u_Textures[26], Input.TexCoord * Input.TilingFactor); break;
		case 27: texColour *= texture(u_Textures[27], Input.TexCoord * Input.TilingFactor); break;
		case 28: texColour *= texture(u_Textures[28], Input.TexCoord * Input.TilingFactor); break;
		case 29: texColour *= texture(u_Textures[29], Input.TexCoord * Input.TilingFactor); break;
		case 30: texColour *= texture(u_Textures[30], Input.TexCoord * Input.TilingFactor); break;
		case 31: texColour *= texture(u_Textures[31], Input.TexCoord * Input.TilingFactor); break;
	}
	colour = texColour;
	colour2 = v_EntityID;
}
