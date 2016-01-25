// Copyright(c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_RENDERERENUMS_H
#define ENGINE_RENDERER_RENDERERENUMS_H

namespace engine {
namespace renderer {

	static const unsigned MAX_INPUTLAYOUT_SIZE = 15;

	enum ShaderType
	{
		SHADERTYPE_INVALID = 0,
		SHADERTYPE_VERTEX,
		SHADERTYPE_PIXEL,
	};

	enum BufferType
	{
		BUFFERTYPE_INVALID = 0,
		BUFFERTYPE_VERTEX,
		BUFFERTYPE_INDEX,
		BUFFERTYPE_CONSTANT,
	};

	enum PrimitiveTopology
	{
		PRIMITIVETOPOLOGY_TRIANGLELIST = 0,
		PRIMITIVETOPOLOGY_LINELIST,
	};

	enum BufferUsage
	{
		BUFFERUSAGE_STATIC = 0,
		BUFFERUSAGE_DYNAMIC,
	};

	enum Semantic
	{
		SEMANTIC_INVALID = 0,
		SEMANTIC_POSITION,
		SEMANTIC_TEXCOORD,
		SEMANTIC_NORMAL,
		SEMANTIC_COLOR,
	};

	enum InputFormat
	{
		INPUTFORMAT_INVALID = 0,
		INPUTFORMAT_FLOAT_X,
		INPUTFORMAT_FLOAT_XY,
		INPUTFORMAT_FLOAT_XYZ,
		INPUTFORMAT_FLOAT_XYZW,
	};

	static const unsigned InputFormatToSize[] =
	{
		0, // invalid
		sizeof(float) * 1, //FLOAT_X
		sizeof(float) * 2, //FLOAT_XY
		sizeof(float) * 3, //FLOAT_XYZ
		sizeof(float) * 4, //FLOAT_XYZW
	};

	enum CullMode
	{
		CULL_NONE = 0,
		CULL_FRONT,
		CULL_BACK,
	};

	enum FillMode
	{
		FILL_WIREFRAME = 0,
		FILL_SOLID,
	};

	enum BlendMode
	{
		BLEND_NONE = 0,
		BLEND_MAX,
		BLEND_ADD,
	};

	enum SamplerState
	{
		DEFAULT_SAMPLER = 0,
	};

	enum TextureType
	{
		TEXTURETYPE_NORMAL = 0,
		TEXTURETYPE_CUBEMAP,
	};

}
}

#endif