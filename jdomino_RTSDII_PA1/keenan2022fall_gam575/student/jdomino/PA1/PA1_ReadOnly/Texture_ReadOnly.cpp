//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Texture.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Texture::Texture(char *pInData, unsigned int _DataSize)
{
	this->poData = new char[_DataSize]();
	assert(this->poData);
	memcpy(this->poData, pInData, _DataSize);

	this->DataSize = _DataSize;
}

Texture::~Texture()
{
	delete this->poData;
}

void Texture::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("    DataSize: %d \n", this->DataSize);
	Trace::out("       CRC32: 0x%x \n", CRC32::GetCRC(this->poData, this->DataSize));
	
	if(this->poData != nullptr)
	{
		Trace::out("        data: %x %x %x %x \n",
			(unsigned char)this->poData[0],
			(unsigned char)this->poData[1],
			(unsigned char)this->poData[2],
			(unsigned char)this->poData[3]
		);
	}
}

// --- End of File ---
