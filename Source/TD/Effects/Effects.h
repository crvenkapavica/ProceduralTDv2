// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effects.generated.h"

UENUM()
enum class EModifier
{
	None,
	MoveSpeed
};

UENUM()
enum class EModifierType
{
	None,
	Single,
	Aura,
	Spread
};

USTRUCT()
struct FEffect
{
	GENERATED_BODY()

	FEffect()
	: Modifier(EModifier::None)
	, ModifierType(EModifierType::None)
	, InitialValue(0.f)
	, Value(0.f)
	, Duration(0.f)
	, Level(0)
	, bStackable(false)
	, bInitialHit(false)
	, ID(-1)
	{ }

	bool operator==(const FEffect& Other) const
	{
		return Modifier == Other.Modifier;
	}

	EModifier Modifier;
	EModifierType ModifierType;

	TArray<FEffect> EffectsUponExpire;
	
	float InitialValue;
	float Value;
	float Duration;
	float Period;
	int32 Level;
	
	bool bStackable;
	bool bInitialHit;
	bool bEffectOnExpire;
	
	int32 ID;
};

UCLASS()
class TD_API AEffects : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffects();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	static FEffect MakeFreezeEffect();

	static FEffect MakeFireEffect();

};
