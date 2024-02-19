#include "Tower.h"
#include "../Creep.h"
#include "../Projectile.h"
#include "EngineUtils.h"
#include "Components/SphereComponent.h"

#include "DrawDebugHelpers.h"


ATower::ATower()
{
	Target = nullptr;

	Range = 200.f;

	PrimaryActorTick.bCanEverTick = true;

	RadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RadiusSphere"));
	RadiusSphere->InitSphereRadius(Range);
	RadiusSphere->SetupAttachment(RootComponent);
	RadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBeginOverlap);
	RadiusSphere->OnComponentEndOverlap.AddDynamic(this, &ATower::OnEndOverlap);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	DrawRadius();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACreep>())
	{
		ACreep* Creep = Cast<ACreep>(OtherActor);
		CreepsInRange.Add(Creep);
		
		OnCreepInRangeAdded(Creep);
	}
	
	if (CreepsInRange.Num())
	{
		Target = CreepsInRange[0];
	}
}

void ATower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<ACreep>())
	{	
		ACreep* Creep = Cast<ACreep>(OtherActor);
		CreepsInRange.Remove(Creep);

		OnCreepInRangeRemoved(Creep);
	}

	if (CreepsInRange.Num() == 0)
	{
		Target = nullptr;
	}
}

void ATower::DrawRadius() const
{
	//float Radius = 3.1415926 * 2 * Range;
	//float _Range = 140.f / 2;  // promeniti ovo
	
	DrawDebugCircle(GetWorld(), GetActorLocation(), Range, 250, FColor::Green, true, -1.f, 0, 3.f,
		FVector(0.f, 1.f, 0.f), FVector(1.0f, 0.f, 0.0f), false);
}
