//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Material.h"

void Material::Serialize(Material_proto &out) const
{
	out.set_x(this->x);
	out.set_a((Material_proto_Color)this->a);
	out.set_b((Material_proto_Color)this->b);
	out.set_c((Material_proto_Color)this->c);
}

void Material::Deserialize(const Material_proto &in)
{
	this->x = in.x();
	this->a = (Color)in.a();
	this->b = (Color)in.b();
	this->c = (Color)in.c();
}

// --- End of File ---
