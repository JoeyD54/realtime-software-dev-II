//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"



StringThis::StringThis(Texture::Name status)
{
	switch (status)
	{
	case Texture::Name::HOT_PINK:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::HOT_PINK));
		break;

	case Texture::Name::STONES:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::STONES));
		break;

	case Texture::Name::RED_BRICK:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::RED_BRICK));
		break;

	case Texture::Name::DUCKWEED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::DUCKWEED));
		break;

	case Texture::Name::ROCKS:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::ROCKS));
		break;

	case Texture::Name::CRATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CRATE));
		break;

	case Texture::Name::BONE_2:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::BONE_2));
		break;

	case Texture::Name::PROTO_LOAD:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::PROTO_LOAD));
		break;

	case Texture::Name::R2D2:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::R2D2));
		break;

	case Texture::Name::CHICKEN_BOT:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CHICKEN_BOT));
		break;

	case Texture::Name::NOT_INITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::NOT_INITIALIZED));
		break;

	default:
		assert(false);
	}
}


StringThis::StringThis(Mesh::Name status)
{
	switch(status)
	{
	case Mesh::Name::CUBE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CUBE));
		break;

	case Mesh::Name::CRATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CRATE));
		break;

	case Mesh::Name::BONE_2:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_2));
		break;

	case Mesh::Name::SPHERE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPHERE));
		break;

	case Mesh::Name::PYRAMID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::PYRAMID));
		break;

	case Mesh::Name::CAMERA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CAMERA));
		break;


	case Mesh::Name::Bone:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone));
		break;

	case Mesh::Name::Bone_001:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_001));
		break;

	case Mesh::Name::Bone_L:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L));
		break;

	case Mesh::Name::Bone_L_001:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L_001));
		break;

	case Mesh::Name::Bone_L_002:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L_002));
		break;

	case Mesh::Name::Bone_R:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R));
		break;

	case Mesh::Name::Bone_R_001:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R_001));
		break;

	case Mesh::Name::Bone_R_002:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R_002));
		break;

	case Mesh::Name::NOT_INITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NOT_INITIALIZED));
		break;

	case Mesh::Name::NULL_MESH:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NULL_MESH));
		break;

	default:
		assert(false);
	}
}



StringThis::StringThis(ShaderObject::Name status)
{
	switch(status)
	{
	case ShaderObject::Name::NULL_SHADER:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::NULL_SHADER));
		break;

	case ShaderObject::Name::COLOR_POSITION:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_POSITION));
		break;

	case ShaderObject::Name::TEXTURE_SIMPLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_SIMPLE));
		break;

	case ShaderObject::Name::TEXTURE_POINT_LIGHT:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_POINT_LIGHT));
		break;

	case ShaderObject::Name::CONST_COLOR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::CONST_COLOR));
		break;

	case ShaderObject::Name::COLOR_SINGLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_SINGLE));
		break;

	case ShaderObject::Name::UNINITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::UNINITIALIZED));
		break;

	default:
		assert(false);
	}
}


StringThis::operator char *()
{
	return this->buffer;
}

// --- End of File ---