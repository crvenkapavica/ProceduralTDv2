#pragma once

#include "CoreMinimal.h"
#include "../Towers/Tower.h"
#include "TowerFreeze.generated.h"

/**
 * 
 */
UCLASS()
class TD_API ATowerFreeze : public ATower
{
	GENERATED_BODY()

public:

	ATowerFreeze();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; 

	virtual void OnCreepInRangeAdded(ACreep* AddedCreep) override;

	virtual void OnCreepInRangeRemoved(ACreep* RemovedCreep) override;
	
};
