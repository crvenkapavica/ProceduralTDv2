#include "TDPlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Towers/Tower.h"

#define _WIN32_WINNT _WIN32_WINNT_WIN10_TH2

ATDPlayerController::ATDPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitBFS();
	SpawnTiles();

	//postavi kx, ky;
	kx = -1; ky = 0;

	SpawnTiles();

	GetWorld()->GetTimerManager().SetTimer(SpawnWaveTimer, this, &ATDPlayerController::SpawnWave, WAVE_TIMER);
	GetWorldTimerManager().SetTimer(NextWaveTimer, WAVE_TIMER, false);

	NextWaveSeconds = WAVE_TIMER + 1;

	SetupHUD();
}

void ATDPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Percent = GetWorldTimerManager().GetTimerElapsed(NextWaveTimer) / NextWaveSeconds;
}

//1 levo
//3 desno
//0 gore
//2 dole

void ATDPlayerController::InitBFS()
{
	col = 500;
	row = 500;

	last = 0;
	curr = 0;
	moves = GetMoves();
	dir = GetDirection();


	BFS(50, 50, 155);
	
	//1 levo
	//3 desno
	//0 gore
	//2 dole
}

void ATDPlayerController::BFS(int x, int y, int maxn)
{
	if (crash) return;
	if (x < 0 || x > col) return;
	if (y < 0 || y > row) return;
	if (map[x][y] == -2) 
	{
		crash = 1;
		return;
	}
	if (map[x][y] > 0) return;
	if (curr == maxn) return;

	/*
	if (map[x + dX[dir]][y + dY[dir]] != 0) {
		dir = GetDirection();
		moves = GetMoves();
		//return;
	}*/

	if (StartX == 0 && StartY == 0)  
	{
		StartX = x * 130.f;
		StartY = y * 130.f;
	}

	++curr;
	map[x][y] = curr;
	posX.Add(x);
	posY.Add(y);
	Orientation.Add(dir);
	last = curr;

	if (--moves) {
		
		if (dir == 0 || dir == 1) {
			if (map[x][y + 1] == 0) {
				map[x][y + 1] = -2;
			}
			if (map[x][y - 1] == 0) {
				map[x][y - 1] = -2;
			}
		}
		else {
			if (map[x + 1][y] == 0) {
				map[x + 1][y] = -2;
			}
			if (map[x - 1][y] == 0) {
				map[x - 1][y] = -2;
			}
		}
	} 
	// add a BACK tile
	else {
		if (dir == 0 || dir == 1)
			dir = FMath::RandRange(2, 3);
		else
			dir = FMath::RandRange(0, 1);
		
		//dir = GetDirection();
		moves = GetMoves();
		
		
		switch (dir) {		
		case 0:
			if (map[x + 1][y] == 0)
				map[x + 1][y] = -1;

			if (map[x][y - 1] == 0)
				map[x][y - 1] = -1;

			if (map[x][y + 1] == 0)
				map[x][y + 1] = -1;
			break;
		case 1:
			if (map[x - 1][y] == 0)
				map[x - 1][y] = -1;

			if (map[x][y + 1] == 0)
				map[x][y + 1] = -1;

			if (map[x][y - 1] == 0)
				map[x][y - 1] = -1;
			break;
		case 2:
			if (map[x][y + 1] == 0)
				map[x][y + 1] = -1;

			if (map[x + 1][y] == 0)
				map[x + 1][y] = -1;

			if (map[x - 1][y] == 0)
				map[x - 1][y] = -1;
			break;
		case 3:
			if (map[x][y - 1] == 0)
				map[x][y - 1] = -1;

			if (map[x - 1][y] == 0)
				map[x - 1][y] = -1;

			if (map[x + 1][y] == 0)
				map[x + 1][y] = -1;
			break;
		}
	}
	
	for (int i = 0; i < 4; i++)
		//BFS(x + dX[(dir + i) % 4], y + dY[(dir + i) % 4], maxn);
		BFS(x + dX[dir], y + dY[dir], maxn);
}

int ATDPlayerController::GetDirection()
{
	return FMath::RandRange(0, 3);
}

int ATDPlayerController::GetMoves()
{
	movesGranted = FMath::RandRange(5, 12);
	return movesGranted;
}

void ATDPlayerController::SpawnTiles()
{
	for (int i = 0; i < last; i++)
		for (int j = 0; j < last; j++)
			if (map[i][j] > 0) {
				FTransform Trans(FVector(i * 130.f, j * 130.f, 111.f));
				GetWorld()->SpawnActor<AActor>(BPMoveTileClass, Trans);
			}
			else if (map[i][j] < 0) {
				FTransform Trans(FVector(i * 130.f, j * 130.f, 111.f));
				GetWorld()->SpawnActor<AActor>(BPBuildTileClass, Trans);
			}
}

void ATDPlayerController::SpawnWave()
{
	GetWorldTimerManager().SetTimer(SpawnCreepTimer, this, &ATDPlayerController::SpawnCreep, CREEP_TIMER, true);
	CurrLevel++;
}

void ATDPlayerController::SpawnCreep()
{
	if (!TotalCreepsSpawnedLevel)
	{
		GetWorldTimerManager().ClearTimer(NextWaveTimer);
		NextWaveSeconds = WAVE_TIMER + CREEP_TIMER * TotalCreepsLevel[CurrLevel];
		GetWorldTimerManager().SetTimer(NextWaveTimer, NextWaveSeconds, false);
	}

	FTransform Trans(FVector(posX[0] * 130.f, posY[0] * 130.f, 111.f));
	GetWorld()->SpawnActor<AActor>(BPWolfClass, Trans);
	TotalCreepsSpawnedLevel++;
		
	if (TotalCreepsSpawnedLevel == TotalCreepsLevel[CurrLevel])
	{
		GetWorldTimerManager().ClearTimer(SpawnCreepTimer);
		TotalCreepsSpawnedLevel = 0;

		if (CurrLevel < MAX_LVLS)
		{
			GetWorldTimerManager().SetTimer(SpawnWaveTimer, this, &ATDPlayerController::SpawnWave, WAVE_TIMER);
		}		
	}
}

void ATDPlayerController::SpawnTower(TSubclassOf<ATower> TowerClass)
{
	FVector Location{ ClickedTile->GetActorLocation() };
	Location += FVector(0.f, 0.f, 100.f);
	FTransform Transform{ Location };
	ATower* Tower = GetWorld()->SpawnActor<ATower>(TowerClass, Transform);
	Tower->AttachToActor(ClickedTile, FAttachmentTransformRules::KeepWorldTransform);
}

void ATDPlayerController::SetupHUD()
{
	NextWaveUIWidget = CreateWidget<UUserWidget>(GetWorld(), BPNextWaveUIClass);
	NextWaveUIWidget->AddToViewport(0);

	BuildUIWidget = CreateWidget<UUserWidget>(GetWorld(), BPBuildUIClass);

	ButtonFreeze = static_cast<UButton*>(BuildUIWidget->GetWidgetFromName(TEXT("ButtonBuildFreeze")));
	if (ButtonFreeze)
		ButtonFreeze->OnClicked.AddDynamic(this, &ATDPlayerController::ButtonFreezeCallback);

	ButtonBounce = static_cast<UButton*>(BuildUIWidget->GetWidgetFromName(TEXT("ButtonBuildBounce")));
	if (ButtonBounce)
		ButtonBounce->OnClicked.AddDynamic(this, &ATDPlayerController::ButtonBounceCallback);
}

void ATDPlayerController::Clicked(AActor* TouchedActor, FKey ButtonPressed)
{
	ClickedTile = TouchedActor;

	if (BuildUIWidget && !BuildUIWidget->IsInViewport())
	{
		BuildUIWidget->AddToViewport(0);
	}
}

void ATDPlayerController::ButtonFreezeCallback()
{
	SpawnTower(BPTowerFreezeClass);
	
	if (BuildUIWidget)
	{ 
		BuildUIWidget->RemoveFromViewport();
	}
}

void ATDPlayerController::ButtonBounceCallback()
{
	SpawnTower(BPTowerBounceClass);

	if (BuildUIWidget)
	{
		BuildUIWidget->RemoveFromViewport();
	}
}