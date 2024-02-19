#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Towers/Tower.h"
#include "Creep.generated.h"

class ATower;
class UProgressBar;

UENUM()
enum EImmunity
{
	MagicImmune
};

USTRUCT()
struct FPassive
{
	GENERATED_BODY()

	FPassive()
	{ }

	EImmunity Immunity;

};

UCLASS()
class TD_API ACreep : public AActor
{
	GENERATED_BODY()
	
public:	

	ACreep();
	
//	TArray<TMap<FEffect, ATower*>> Effects;
	TArray<FPassive> Passives;

	float MoveSpeed;

	float MoveSpeedModifier = 1.f;

	int32 BaseHealth;
	int32 ActualHealth;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthBarUIClass;
	UUserWidget* HealthBarUI;
	UProgressBar* HealthBar;

public:

	void ApplyDamage(int InDamage);



protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Interpolate(float DeltaTime);
	void StartRotate();
	void EdgeRotate();
	
	void DrawHealthBar() const;

private:

	class ATDPlayerController* PC;

	int currIndex = 0;

private:
};
