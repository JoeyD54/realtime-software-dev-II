//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Material.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Material::Material(Color _a, Color _b, Color _c, int _x)
	:x(_x),
	a(_a),
	b(_b),
	c(_c)
{

}

const char *Material::GetString(Color _c) const
{
	const char *pString(nullptr);

	switch(_c)
	{
	case Color::Blue:
		pString = "Blue";
		break;

	case Color::White:
		pString = "White";
		break;

	case Color::Red:
		pString = "Red";
		break;

	case Color::Yellow:
		pString = "Yellow";
		break;

	default:
		pString = "ERROR";
		break;
		
	}

	return pString;
}

void Material::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("    a:%s b:%s c:%s x:%i\n",
		this->GetString(this->a),
		this->GetString(this->b),
		this->GetString(this->c),
		this->x);
}

// --- End of File ---
