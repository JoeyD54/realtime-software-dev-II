//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Mesh.h"

namespace Azul
{
	class CameraMesh : public Mesh
	{
	public:
		CameraMesh(const char *const modelFileName);
		~CameraMesh();

		void update();

		// tells the compiler do not create or allow it to be used, c++11
		CameraMesh(const CameraMesh &) = delete;
		CameraMesh &operator=(const CameraMesh &other) = delete;

	private:
		void privCreateVAO(const char *const modelFileName);

	};

}

#endif

// --- End of File ---
