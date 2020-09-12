#include "WallBottom.h"
#include "LevelManager.h"

void WallBottom::OnCollisionEnter(Component* other)
{
	if (other->GetParent()->GetName() == "Ball")
	{
		LevelManager::GetManager()->LifeLost();
	}
}