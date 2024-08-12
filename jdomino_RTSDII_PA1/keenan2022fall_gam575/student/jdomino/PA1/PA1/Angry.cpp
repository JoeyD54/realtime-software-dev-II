//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Angry.h"

void Angry::Serialize(Angry_proto &out) const
{
	out.add_arr(this->arr[0]);
	out.add_arr(this->arr[1]);
	out.add_arr(this->arr[2]);
	out.add_arr(this->arr[3]);

	out.set_value(this->value);
}

void Angry::Deserialize(const Angry_proto &in)
{
	this->arr[0] = in.arr(0);
	this->arr[1] = in.arr(1);
	this->arr[2] = in.arr(2);
	this->arr[3] = in.arr(3);

	this->value = in.value();
}

// --- End of File ---
