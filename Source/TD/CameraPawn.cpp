#include "CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.h"

ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); 
	CameraBoom->TargetArmLength = 1100.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; 
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<ATDPlayerController>(GetWorld()->GetFirstPlayerController());

	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;

	SetCameraStart();
}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCamera(DeltaTime);
	ZoomIn(DeltaTime);
	ZoomOut(DeltaTime);
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::CameraZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::CameraZoomOut);
}

void ACameraPawn::MoveCamera(float DeltaTime)
{
	AddActorWorldOffset(GetCameraPanDirection() * 2000 * DeltaTime);
}

FVector ACameraPawn::GetCameraPanDirection()
{
	float MousePosX, MousePosY;
	int32 ScreenSizeX, ScreenSizeY;
	float CamDirectionX = 0, CamDirectionY = 0;

	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	PC->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX <= 20.f) {
		CamDirectionX = 1;
	}
	if (MousePosX >= ScreenSizeX - 20.f) {
		CamDirectionX = -1;
	}
	if (MousePosY <= 20.f) {
		CamDirectionY = 1;
	}
	if (MousePosY >= ScreenSizeY - 20.f) {
		CamDirectionY = -1;
	}
	return FVector(CamDirectionX, CamDirectionY, 0.f);
}

void ACameraPawn::CameraZoomIn()
{
	CameraBeforeZoom = GetActorLocation().Z;
	bZoomingIn = true;
}

void ACameraPawn::CameraZoomOut() 
{
	CameraBeforeZoom = GetActorLocation().Z;
	bZoomingOut = true;
}

void ACameraPawn::ZoomIn(float DeltaTime)
{
	if (bZoomingIn)
	{
		if (GetActorTransform().GetLocation().Z > 100.f) {
			FVector Curr = GetActorLocation();
			FVector End = GetActorLocation() + FVector(0.f, 0.f, -200.f);
			Curr = FMath::VInterpTo(Curr, End, DeltaTime, 3.f);

			SetActorLocation(Curr);
			if (CameraBeforeZoom - Curr.Z >= 150) {
				bZoomingIn = false;
			}
		}
		else
		{
			bZoomingIn = false;
		}
	}
}

void ACameraPawn::ZoomOut(float DeltaTime)
{
	if (bZoomingOut)
	{
		if (GetActorTransform().GetLocation().Z < 2200.f)
		{
			FVector Curr = GetActorLocation();
			FVector End = GetActorLocation() - FVector(0.f, 0.f, -200.f);
			Curr = FMath::VInterpTo(Curr, End, DeltaTime, 3.f);

			SetActorLocation(Curr);
			if (Curr.Z - CameraBeforeZoom >= 150) {
				bZoomingOut = false;
			}
		}
		else
		{
			bZoomingOut = false;
		}
	}
}

void ACameraPawn::SetCameraStart()
{
	int ScreenSizeX;
	int ScreenSizeY;
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	SetActorLocation(FVector(PC->StartX, PC->StartY, 750.f));
	SetActorRotation(FRotator(-60.f, 90.f, 0.f));
}
