// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnSystem.generated.h"

UCLASS()
class TRENCHCOATSGAME_API ASpawnSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SettingSpawnParamters();
	FVector SettingSpawnLocation(float spawnPointNumber);
	void SpawningEnemy();


#pragma region SPAWNING NUMBERS

	//Keeping track of current round
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int currentRound;

	//This keeps track of how many enemies have spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int numberOfEnemiesSpawned;
	//How many soldiers to spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int numberOfSoldiers;
	//How many medics to spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int numberOfMedics;

#pragma endregion

#pragma region SPAWN POINTS


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* RootSpawn;

	//Places where the enemy can spawn 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMesh* spawnPoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMesh* spawnPoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMesh* spawnPoint3;


#pragma endregion

	//Location of spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool roundStart;
	
};
