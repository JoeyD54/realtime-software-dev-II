//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Angry.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Angry::Angry(int x0, int x1, int x2, int x3, float _value)
{
	this->arr[0] = x0;
	this->arr[1] = x1;
	this->arr[2] = x2;
	this->arr[3] = x3;
	this->value = _value;

}

void Angry::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);

	for(int i = 0; i < Angry::N; i++)
	{
		Trace::out("    a[%d]: %d\n", i, this->arr[i]);
	}
	Trace::out("    value: %f \n", this->value);
}

// --- End of File ---
