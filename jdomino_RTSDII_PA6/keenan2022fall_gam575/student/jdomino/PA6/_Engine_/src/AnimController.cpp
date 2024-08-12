//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"

namespace Azul
{
	AnimController::AnimController(AnimTime delta, Skeleton::Position pos, Clip* clip)
	{
		// Animation object
		this->poAnim = new Anim(pos, clip);
		assert(this->poAnim);

		// TimerController
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->poTimerControl);

	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerControl;
	}

	void AnimController::Update()
	{
		this->poTimerControl->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime());

	}

	void AnimController::SetLocation(Skeleton::Position newPos)
	{
		this->poAnim->SetLocation(newPos);
	}
}

// --- End of File ---
