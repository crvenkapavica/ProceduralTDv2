#include "../Towers/TowerBounce.h"
#include "../Projectile.h"
#include "../Creep.h"

ATowerBounce::ATowerBounce()
{
	Speed = 120.f;
	Damage = 5;
}

void ATowerBounce::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATowerBounce::Attack, 5.f, true, 0.f);

}

void ATowerBounce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerBounce::Attack()
{
	if (Target)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorTransform());
		Projectile->Target = Target;
		Projectile->Owner = this;
		Projectile->bIsBounce = true;
		Projectile->NumBounces = 5;
	}
}

void ATowerBounce::ApplyBounceAura()
{
	UE_LOG(LogTemp, Warning, TEXT("BURNING"));
}
