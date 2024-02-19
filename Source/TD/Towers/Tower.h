#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Effects/Effects.h"
#include "Tower.generated.h"

class ACreep;
class AProjectile;
class USphereComponent;

UCLASS()
class TD_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	TArray<FEffect> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;

	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectileClass;

	TArray<ACreep*> CreepsInRange;

	int Level = 1;

	int MaxLevel;

protected:

	ACreep* Target;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditAnywhere)
	USphereComponent* RadiusSphere;

protected:

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void OnCreepInRangeAdded(ACreep* AddedCreep) { }; // PURE VIRTUAL MAYBE ?

	virtual void OnCreepInRangeRemoved(ACreep* RemovedCreep) { }; 

	float Radius = 125.f;

protected:
	
	void DrawRadius() const;

};
