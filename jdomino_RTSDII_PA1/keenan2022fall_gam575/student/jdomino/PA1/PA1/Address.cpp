//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Address.h"

void Address::Serialize(Address_proto &out) const
{
	std::string poAddrStr(this->poAddr, N);
	std::string poNameStr(this->poName, N);
	std::string poPhoneStr(this->poPhone, N);

	out.set_poaddr(poAddrStr);
	out.set_poname(poNameStr);
	out.set_pophone(poPhoneStr);
}

void Address::Deserialize(const Address_proto &in)
{
	memcpy(this->poAddr, in.poaddr().data(), N);
	memcpy(this->poName, in.poname().data(), N);
	memcpy(this->poPhone, in.pophone().data(), N);
}

// --- End of File ---
