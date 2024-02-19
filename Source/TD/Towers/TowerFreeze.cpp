#include "../Towers/TowerFreeze.h"
#include "../Creep.h"
#include "../TDPlayerController.h"
#include "../Effects/Effects.h"

ATowerFreeze::ATowerFreeze()
{
	
}

void ATowerFreeze::BeginPlay()
{
	Super::BeginPlay();

	Effects.Add(AEffects::MakeFreezeEffect());
}

void ATowerFreeze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerFreeze::OnCreepInRangeAdded(ACreep* AddedCreep)
{
	
}

void ATowerFreeze::OnCreepInRangeRemoved(ACreep* RemovedCreep)
{
	//RemovedCreep->RemoveEffect(Effects[0]);	
}
