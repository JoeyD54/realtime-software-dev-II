//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Texture.h"

void Texture::Serialize(Texture_proto &out) const
{
	std::string dataStr(this->poData, this->DataSize);
	out.set_podata(dataStr);
	out.set_datasize(this->DataSize);
}

void Texture::Deserialize(const Texture_proto &in)
{
	this->DataSize = in.datasize();

	this->poData = new char[this->DataSize];
	assert(this->poData);

	memcpy(this->poData, in.podata().data(), this->DataSize);
}

// --- End of File ---
