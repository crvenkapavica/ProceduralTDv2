#include "Creep.h"

#include <wrl/implements.h>

#include "TDPlayerController.h"
#include "Towers/Tower.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "TDPlayerController.h"

#include "Kismet/GameplayStatics.h"

ACreep::ACreep()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreep::ApplyDamage(int InDamage)
{
	// TODOs
}

void ACreep::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<ATDPlayerController>(GetWorld()->GetFirstPlayerController());
	StartRotate();

	MoveSpeed = PC->MoveSpeedLevel[PC->CurrLevel];
	BaseHealth = ActualHealth = PC->HealthLevel[PC->CurrLevel];

	HealthBarUI = CreateWidget<UUserWidget>(GetWorld(), HealthBarUIClass);
	HealthBarUI->AddToViewport(0);
	HealthBarUI->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	HealthBar = static_cast<UProgressBar*>(HealthBarUI->GetWidgetFromName(TEXT("HealthBar")));
}

void ACreep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawHealthBar();
	Interpolate(DeltaTime);

	if (ActualHealth <= 0)
	{
		HealthBarUI->RemoveFromViewport();
		Destroy();
	}
}

void ACreep::Interpolate(float DeltaTime)
{
	if (currIndex < PC->posX.Num())
	{
		float x = GetActorLocation().X;
		float y = GetActorLocation().Y;
		const float destX = PC->posX[currIndex] * 130.f;
		const float destY = PC->posY[currIndex] * 130.f;

		if (FMath::Abs(destX - x) >= 1.f)
		{
			x = FMath::FInterpConstantTo(x, destX, DeltaTime, 60.f * MoveSpeed * MoveSpeedModifier);
		}
		else if (FMath::Abs(destY - y) >= 1.f) 
		{
			y = FMath::FInterpConstantTo(y, destY, DeltaTime, 60.f * MoveSpeed * MoveSpeedModifier);
		}
		else
		{
			currIndex++;

			if (currIndex < PC->Orientation.Num() && PC->Orientation[currIndex] != PC->Orientation[currIndex - 1])
			{
				EdgeRotate();
			}
		}
		SetActorLocation(FVector(x, y, 150));
	}
	else
	{
		Destroy();
	}
}

void ACreep::StartRotate()
{
	switch (PC->Orientation[0])
	{
	case 0:
		AddActorWorldRotation(FRotator(0.f, 90.f, 0.f));
		break;
	case 1:
		AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		break;
	case 2:
		AddActorWorldRotation(FRotator(0.f, 180.f, 0.f));
		break;
	default:
		break;
	}
}

void ACreep::EdgeRotate()
{
	if (currIndex) {
		switch (PC->Orientation[currIndex]) 
		{
		case 3:
			SetActorRotation(FRotator(0.f, 0.f, 0.f));
			break;
		case 2:
			SetActorRotation(FRotator(0.f, 180.f, 0.f));
			break;
		case 1:
			SetActorRotation(FRotator(0.f, -90.f, 0.f));
			break;
		case 0:
			SetActorRotation(FRotator(0.f, 90.f, 0.f));
			break;
		default:
			break;
		}
	}
}

void ACreep::DrawHealthBar() const
{
	FVector2D ScreenLocation;
	const ATDPlayerController* Player = Cast<ATDPlayerController>(GetWorld()->GetFirstPlayerController());
	Player->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);
	HealthBarUI->SetPositionInViewport(ScreenLocation);

	const float Percent = ActualHealth / BaseHealth;
	HealthBar->SetPercent(Percent);
}


