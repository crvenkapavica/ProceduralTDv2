
#include "../Effects/Effects.h"

AEffects::AEffects()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEffects::BeginPlay()
{
	Super::BeginPlay();
}

void AEffects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FEffect AEffects::MakeFreezeEffect()
{
	FEffect FreezeEffect;
	FreezeEffect.Modifier = EModifier::MoveSpeed;
	FreezeEffect.ModifierType = EModifierType::Aura;
	FreezeEffect.Duration = 0.f;
	FreezeEffect.Value = 0.3f;
	FreezeEffect.Level = 1;
	FreezeEffect.bStackable = false;
	FreezeEffect.bInitialHit = false;
	FreezeEffect.ID = 1;

	return FreezeEffect;
}

FEffect AEffects::MakeFireEffect()
{
	FEffect FireEffect;
	FireEffect.ModifierType = EModifierType::Spread;
	FireEffect.Duration = 3.f;
	FireEffect.Value = 0.3f;
	FireEffect.Level = 1;
	FireEffect.bStackable = true;
	FireEffect.bInitialHit = false;
	FireEffect.ID = 1;

	return FireEffect;
}

