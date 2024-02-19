#include "Projectile.h"
#include "Creep.h"
#include "Towers/Tower.h"
#include "EngineUtils.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Interpolate(DeltaTime);
}

void AProjectile::Interpolate(float DeltaTime)
{
	FVector Current = FMath::VInterpConstantTo(GetActorLocation(), Target->GetActorLocation(), DeltaTime, 350.f);
	SetActorLocation(Current);

	if (FVector::Dist(GetActorLocation(), Target->GetActorLocation()) < 2.f)
	{
		Target->ApplyDamage(Owner->Damage);

		if (bIsBounce && NumBounces)
		{
			float MinDistance = 9999999.f;
			for (TActorIterator<ACreep> Iter(GetWorld()); Iter; ++Iter)
			{
				float Distance = FVector::Dist(GetActorLocation(), Iter->GetActorLocation());
				if (Distance <= MinDistance && Distance > 2.f)
				{
					MinDistance = Distance;
					Target = *Iter;
				}
			}
			--NumBounces;
		}
		else
		{
			Destroy();
		}
	}
}

