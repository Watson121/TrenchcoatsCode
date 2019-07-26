// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnSystem.h"


// Sets default values
ASpawnSystem::ASpawnSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnRootMesh"));
	RootComponent = RootSpawn;

	spawnPoint1 = CreateDefaultSubobject<UStaticMesh>(TEXT("SpawnPoint1"));
	spawnPoint2 = CreateDefaultSubobject<UStaticMesh>(TEXT("SpawnPoint2"));
	spawnPoint3 = CreateDefaultSubobject<UStaticMesh>(TEXT("SpawnPoint3"));

	roundStart = true;

	currentRound = 1;

}

// Called when the game starts or when spawned
void ASpawnSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnSystem::Tick(float DeltaTime)
{

	SettingSpawnParamters();
	location = SettingSpawnLocation(FMath::RandRange(0, 3));

	Super::Tick(DeltaTime);

	

}

void ASpawnSystem::SettingSpawnParamters() {
	if (roundStart == true) {
		if (currentRound == 1) {
			numberOfSoldiers = 10;
			numberOfMedics = 0;
		}
		else if (currentRound == 2) {
			numberOfSoldiers = 10;
			numberOfMedics = 5;
		}
		else if (currentRound == 3) {
			numberOfSoldiers = 15;
			numberOfMedics = 5;
		}
		
	}
}

FVector ASpawnSystem::SettingSpawnLocation(float spawnPointNumber) {

	FVector spawnPoint;
	spawnPoint = FVector(-250.0f, 185.0f, 0.0f);

	return spawnPoint;
}

void ASpawnSystem::SpawningEnemy() {

}




