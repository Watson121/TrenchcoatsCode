// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "RubyPistolV2.h"
#include "FrenchRifle.h"
#include "MedicBag.h"
#include "Engine.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	playerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Player Root"));
	RootComponent = playerRoot;

	vrOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	vrOrigin->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(vrOrigin);

	camera->bLockToHmd = true;

	DefaultCharacterHeight = 160;
	FadeOutDuration = 0.1f;
	FadeInDuraction = 0.2f;

	leftHand = false;
	rightHand = false;

	currentPlayerHealth = 70;
	fullPlayerHealth = 100;

	BaseEyeHeight = 180;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	HMDDeviceName = GetHMDDeviceName();
	
	for (TActorIterator<ARubyPistolV2> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		rubyPistol = *ActorItr;
	}

	for (TActorIterator<AFrenchRifle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		frenchRifle = *ActorItr;
	}

	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Reload", IE_Pressed, this, &APlayerPawn::SendReloadMessage);
	InputComponent->BindAction("FireLeft", IE_Pressed, this, &APlayerPawn::SendLeftFireMessage);
	InputComponent->BindAction("FireRight", IE_Pressed, this, &APlayerPawn::SendRightFireMessage);

}



//SEND MESSAGE FUNCTIONS

void APlayerPawn::SendReloadMessage() {
	//if (pistolPickedUp) {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
	//	rubyPistol->Reload();
	//}

	//if (riflePickedUp) {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
	//	frenchRifle->Reload();
	//}
	
	if (medicBagPickedUp) {
		HealPlayer(20);
		medicBag->DestroyThis();
	}
}

void APlayerPawn::SendLeftFireMessage() {
	if (pistolPickedUp) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
		leftHand = true;
		rubyPistol->FireLeft();
	}

	if (riflePickedUp) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
		leftHand = true;
		frenchRifle->FireLeft();
	}

}

void APlayerPawn::SendRightFireMessage() {
	if (pistolPickedUp) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
		rubyPistol->FireRight();
	}

	if (riflePickedUp) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
		frenchRifle->FireRight();
	}

}


//PLAYERS STATS

void APlayerPawn::HealPlayer(float healAmount) {
	currentPlayerHealth = currentPlayerHealth + healAmount;
}

void APlayerPawn::TakeAwayHealth() {
	currentPlayerHealth = currentPlayerHealth - 5;
}


//GET FUNCTIONS

bool APlayerPawn::GetPistol() {
	return pistolPickedUp;
}

FName APlayerPawn::GetHMDDeviceName() {

//This function gets the HMD Device Name

	FName deviceName;

	if (GEngine->XRSystem.IsValid()) {
		deviceName = GEngine->XRSystem->GetSystemName();
	}

	return deviceName;
}

bool APlayerPawn::GetLeftHand() {
	return leftHand;
}

bool APlayerPawn::GetRightHand() {
	return rightHand;
}

//SETTER FUNCTIONS

void APlayerPawn::SetMedicBag(class AMedicBag* medic) {
	medicBag = medic;
}







