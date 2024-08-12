//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "Keyboard.h"

extern Game *pGame;

// Use this to read keyboard
bool Keyboard::GetKeyState(Keyboard::Key key)
{
	bool value;

	if (pGame->GetKey(key) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}

// --- End of File ---
