// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Creep.h"
#include "TDPlayerController.generated.h"

#define MAX_LVLS 10
#define WAVE_TIMER 12
#define CREEP_TIMER 1

class UButton;
class ATower;
class USphereComponent;

/**
 * 
 */
UCLASS()
class TD_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BPMoveTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BPBuildTileClass;

	//*****************************************
	//===============UI========================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BPBuildUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BPNextWaveUIClass;
	//=========================================
	
	UUserWidget* BuildUIWidget;
	UUserWidget* NextWaveUIWidget;

	UButton* ButtonFreeze;
	UButton* ButtonBounce;

	//*****************************************
	//=============TOWERS======================
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATower> BPTowerFreezeClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATower> BPTowerBounceClass;
	//==========================================
	
	//*****************************************
	//=============CREEPS======================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACreep> BPWolfClass;
	//==========================================

	//******************************************
	//===========CREEP SHEET====================
	TArray<int> HealthLevel = {
		7, 12, 21, 35, 54, 70, 101, 189, 211, 370
	};

	TArray<float> MoveSpeedLevel = {
		1.5, 1.0, 1.2, 1.3, 1.5, 1.5, 2, 1.2, 1.5, 1.6
	};

	TArray<int> TotalCreepsLevel = {
		5, 7, 2, 10, 10, 1, 10, 11, 15, 15
	};
	//==========================================

	UFUNCTION(BlueprintCallable)
	float GetNextWavePercent() { return Percent; }

	float Percent = 0.f;

	TArray<int> posX, posY;
	TArray<int> Orientation;

	int32 CurrLevel = 0;
	int32 TotalCreepsSpawnedLevel = 0;

	UFUNCTION(BlueprintCallable)
	void Clicked(AActor* TouchedActor, FKey ButtonPressed);

	UPROPERTY(BlueprintReadWrite)
	AActor* ClickedTile;

protected:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

/// <summary>
/// Map generator
/// </summary>
private:

	void InitBFS();
	void BFS(int x, int y, int maxn);

	int GetDirection();
	int GetMoves();

	bool crash = 0;

	int dX[4] = { -1, 1, 0, 0 };
	int dY[4] = { 0, 0, -1, 1 };

	int col, row;
	int curr = 0;
	int moves, movesGranted;
	int dir;
	int last;

	int map[1001][1001] = { 0 };

public:

	float StartX = 0, StartY = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

	FTimerHandle SpawnWaveTimer;
	FTimerHandle SpawnCreepTimer;
	FTimerHandle NextWaveTimer;

	int32 NextWaveSeconds;

	void SpawnTiles();
	void SpawnWave();
	void SpawnCreep();
	void SpawnTower(TSubclassOf<ATower> TowerClass);

	UFUNCTION()
	void ButtonFreezeCallback();

	UFUNCTION()
	void ButtonBounceCallback();

	void SetupHUD();



	//////////////////////////////


	TArray<int> MovesLeftAtDirection = {
		35,
		60,
		35,
		60
	};

	int dSign[4] = { -1, -1, 1, 1 };
	char dAxis[4] = { 'x', 'y', 'x', 'y' };

	int lastDirSign = 0;
	
	int kx, ky;

	int MainDirectionMoves = 0;

	int lastX, lastY;

	int MainDirection = 1;

	int lastDir = -2;
};
