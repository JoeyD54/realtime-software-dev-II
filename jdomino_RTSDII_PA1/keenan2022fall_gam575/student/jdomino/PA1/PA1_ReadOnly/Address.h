//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef ADDRESS_H
#define ADDRESS_H

#include "Address.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Address
{
public:
	static const unsigned int N = 64;

public:
	Address();
	Address(const Address &) = delete;
	Address &operator = (const Address &) = delete;
   ~Address();

	Address(const char *pName, const char *pAddr, const char *pPhone);

	// Serialization 
	void Serialize(Address_proto &out) const;
	void Deserialize(const Address_proto &in);

	void Print(const char *const pName) const;

public:
	char *poName;   // allocation size is known... no need to serialize size
	char *poAddr;   // allocation size is known... no need to serialize size
	char *poPhone;  // allocation size is known... no need to serialize size
};

#endif

// --- End of File ---
