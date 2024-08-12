//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"

namespace Azul
{
	class AnimController
	{
	public:
		AnimController(AnimTime delta, Skeleton::Position pos, Clip* clip);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void SetLocation(Skeleton::Position newPos);
		void Update();

	private:
		TimerController *poTimerControl;
		Anim *poAnim;

	};
}

#endif

// --- End of File ---
