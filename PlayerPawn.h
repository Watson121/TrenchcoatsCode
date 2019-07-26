// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "IXRSystemAssets.h"
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplay.h"
#include "HeadMountedDisplayBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class ARubyPistolV2;
class AFrenchRifle;
class AMedicBag;

UCLASS()
class TRENCHCOATSGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

private:

	// Called when the game starts or when spawned
	





protected:

	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void SendReloadMessage();
	void SendLeftFireMessage();
	void SendRightFireMessage();
	void HealPlayer(float healAmount);

	UFUNCTION(BlueprintCallable)
		void TakeAwayHealth();

	UFUNCTION()
	virtual bool GetPistol();

	UFUNCTION()
	FName GetHMDDeviceName();

	void SetMedicBag(class AMedicBag* medic);


	//Functions Related to Player Health
	//UFUNCTION()
	//	virtual int GetPlayerHealth() override;
	//UFUNCTION()
	//	virtual void TakePlayerHealth(int damage) override;
	//UFUNCTION()
	//	virtual void CheckPlayerHealth() override;

	virtual bool GetLeftHand();
	virtual bool GetRightHand();

	//Scene Componenets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* playerRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* vrOrigin;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* camera;

	//floats
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float FadeOutDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float FadeInDuraction;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float ThumbDeadzone;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DefaultCharacterHeight;

	//ints
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int PistolAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int RifleAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float currentPlayerHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float fullPlayerHealth;

	//Bools
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsTeleporting;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool RightStickDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool LeftStickDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool UseControllerRollToRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool leftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rightHand;

	//Fname
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName HMDDeviceName;

	UPROPERTY(EditAnywhere)
	ARubyPistolV2* rubyPistol;
	UPROPERTY(EditAnywhere)
	AFrenchRifle* frenchRifle;
	UPROPERTY(EditAnywhere)
	AMedicBag* medicBag;

	//Pick up Objects

	//Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool pistolPickedUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool riflePickedUp;


	//Other Items
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool medicBagPickedUp;

	

};
