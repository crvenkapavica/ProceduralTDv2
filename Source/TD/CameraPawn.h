// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class TD_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveCamera(float DeltaTime);

	FVector GetCameraPanDirection();

	void CameraZoomIn();
	void CameraZoomOut();

	void ZoomIn(float DeltaTime);
	void ZoomOut(float DeltaTime);

	bool bZoomingIn = false, bZoomingOut = false;

	float CameraBeforeZoom;

	void SetCameraStart();

	class USpringArmComponent* CameraBoom;
	
	class UCameraComponent* Camera;

	class ATDPlayerController* PC;
};
