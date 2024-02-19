#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class ACreep;
class ATower;

UCLASS()
class TD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	ACreep* Target;

	ATower* Owner;

	bool bIsBounce;
	int NumBounces = 0;

protected:

	void Interpolate(float DeltaTime);


};
