//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Address.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Address::Address()
{
	this->poName = new char[Address::N]();
	assert(this->poName);

	this->poAddr = new char[Address::N]();
	assert(this->poAddr);

	this->poPhone = new char[Address::N]();
	assert(this->poPhone);

	memset(this->poName, 0x0, Address::N);
	memset(this->poAddr, 0x0, Address::N);
	memset(this->poPhone, 0x0, Address::N);
}

Address::Address(const char *pName, const char *pAddr, const char *pPhone)
{
	assert(pName);
	assert(pAddr);
	assert(pPhone);

	this->poName = new char[Address::N]();
	assert(this->poName);

	this->poAddr = new char[Address::N]();
	assert(this->poAddr);

	this->poPhone = new char[Address::N]();
	assert(this->poPhone);

	memset(this->poName, 0x0, Address::N);
	memset(this->poAddr, 0x0, Address::N);
	memset(this->poPhone, 0x0, Address::N);

	memcpy(this->poName, pName, Address::N - 1);
	memcpy(this->poAddr, pAddr, Address::N - 1);
	memcpy(this->poPhone, pPhone, Address::N - 1);
}

Address::~Address()
{
	delete[] this->poName;
	delete[] this->poAddr;
	delete[] this->poPhone;
}

void Address::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);

	Trace::out("    Name: %s \n", this->poName);
	Trace::out("    Addr: %s \n", this->poAddr);
	Trace::out("   Phone: %s \n", this->poPhone);
}

// --- End of File ---
