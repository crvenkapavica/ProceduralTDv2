#pragma once

#include "CoreMinimal.h"
#include "../Towers/Tower.h"
#include "TowerBounce.generated.h"

/**
 * 
 */
UCLASS()
class TD_API ATowerBounce : public ATower
{
	GENERATED_BODY()

public:

	ATowerBounce();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void Attack();

protected:

	static void ApplyBounceAura();

public:

	int NumBounces;
};
