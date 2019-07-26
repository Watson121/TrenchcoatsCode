// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RubyPistolV2.generated.h"

class AGermanSoldier;
class AGermanMedicV2;
class APlayerPawn;

UCLASS()
class TRENCHCOATSGAME_API ARubyPistolV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARubyPistolV2();

private:

	virtual void RemoveAmmo();


#pragma region AUDIO FUNCTIONS

	virtual void PlayGunShotAudio();

#pragma endregion



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWorld* World;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Booleans - related to tracking if gun has been picked up, and which hand it is in

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool pickedUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool leftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rightHand;

#pragma endregion

#pragma region MESHES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* pistolMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* firingMeshPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* pistol;


#pragma endregion

#pragma region VARIABLES FOR FINDING THE PLAYER PAWN, AND GETTING NAME OF CURRENT HAND THE GUN IS HOLDING
	UPROPERTY(EditAnywhere)
		APawn* playerPawn;
	UPROPERTY(EditAnywhere)
		APlayerPawn* playerPawnClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* currentHand; //Finds the current hand, the pistol is currently being held by
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nameOfHand; //Takes ID of the current hand
#pragma endregion

#pragma region AUDIO
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* pistolShotSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* pistolReloadSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* pistolClickSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* pistolAudioComponent;
#pragma endregion


#pragma region PARTICLE EFFECTS

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* pistolParticleSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* muzzleFlashParticle;

#pragma endregion

#pragma region PISTOL STATS
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ammoClip;
#pragma endregion

#pragma region PISTOL FUNCTIONS
	void FireLeft(); // function related to firing with the left hand
	void FireRight();	//function related to firing with the right hand
	UFUNCTION(BlueprintCallable)
		void Reload();	//function related to reloading the gun
#pragma endregion

#pragma region GETTER FUNCTIONS
	virtual bool GetPickedUp();
	virtual int GetAmmoClip();
	void ShootingRaycast();
#pragma endregion


#pragma region OTHER ACTORS

	//Getting Enemy class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AGermanSoldier* enemySoldier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AGermanMedicV2* enemyMedic;

#pragma endregion
};
