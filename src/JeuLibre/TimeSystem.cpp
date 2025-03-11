#include "pch.h"
#include "TimeSystem.h"

float TimeSystem::GetDeltaTime() {
	return DeltaTime; 
}
void TimeSystem::UpdateDeltaTime() {
	DeltaTime = clock.restart().asSeconds();
}
