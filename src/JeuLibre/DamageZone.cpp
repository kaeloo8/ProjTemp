#include "pch.h"
#include "DamageZone.h"

void DamageZone::OnUpdate() {

	if (LifeTime >= 0) {
		LifeTime -= GameManager::Get()->GetDeltaTime();
	}
	else {
		this->Destroy();
	}

}

void DamageZone::OnCollision(Entity* pCollidedWith) {
	
	std::cout << pCollidedWith << std::endl;
	for (int tag : lTagIgnore) {
		if (pCollidedWith->mTag == tag) {
			return; 
		}
	}
	//pCollidedWith->DamageLife(Damage);
	pCollidedWith->Destroy();
	if (UniqueColide) {
		Destroy();
	}
}