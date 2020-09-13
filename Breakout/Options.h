#pragma once
#include "SoundManager.h"
#include "Rect.h"

namespace options
{
	void SetVolume(int number)
	{
		SoundManager::GetManager()->ChangeMasterVolume(number);
	}

	void ChangeAspectRatio(Vector2 ratio)
	{
		Rect::SetResolutionRatio(ratio, false);
	}
}