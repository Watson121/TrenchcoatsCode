// Fill out your copyright notice in the Description page of Project Settings.

#include "RubyPistolV2.h"
#include "GermanMedicV2.h"
#include "GermanSoldier.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "EngineUtils.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <SceneInterface.h>
#include "Engine.h"

// Sets default values
ARubyPistolV2::ARubyPistolV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pistolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pistol Mesh"));
	firingMeshPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front of Gun"));
	firingMeshPos->bEditableWhenInherited = true;

	firingMeshPos->SetupAttachment(pistolMesh);

	firingMeshPos->SetRelativeLocation(FVector(0, 2.0f, -6.0f));
	//firingMeshPos->SetRelativeRotation(FRotator(180, -90, 180));

	//MESHES
	static ConstructorHelpers::FObjectFinder<UStaticMesh> pistolMeshObject(TEXT("StaticMesh'/Game/Assets/Models/RubyPistolUV.RubyPistolUV'"));
	pistol = pistolMeshObject.Object;

	if (pistol) {
		pistolMesh->SetStaticMesh(pistol);
	}

	//AUDIO
	static ConstructorHelpers::FObjectFinder<USoundWave> pistolShot(TEXT("SoundWave'/Game/Assets/Audio/PistolShot.PistolShot'"));
	pistolShotSound = pistolShot.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> pistolReload(TEXT("SoundWave'/Game/Assets/Audio/396331__nioczkus__1911-reload.396331__nioczkus__1911-reload'"));
	pistolReloadSound = pistolReload.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> pistolClick(TEXT("SoundWave'/Game/Assets/Audio/Pistol_Hammer_Cock_02.Pistol_Hammer_Cock_02'"));
	pistolClickSound = pistolClick.Object;

	pistolAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PistolAudioComponent"));
	pistolAudioComponent->bAutoActivate = false;

	if (pistolShotSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolShotSound);
	}

	//Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> pistolFire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_MuzzleFlash.P_MuzzleFlash'"));
	muzzleFlashParticle = pistolFire.Object;

	pistolParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PistolParticleSystem"));
	pistolParticleSystem->bAutoActivate = false;

	if (muzzleFlashParticle->IsValidLowLevelFast()) {
		pistolParticleSystem->SetTemplate(muzzleFlashParticle);
	}

	World = GetWorld();
}

// Called when the game starts or when spawned
void ARubyPistolV2::BeginPlay()
{
	/*playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
bBlockInput = false;*/

	for (TActorIterator<APlayerPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		playerPawnClass = *ActorItr;
	}


	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ammoClip = 8;

	Super::BeginPlay();
	
}

// Called every frame
void ARubyPistolV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARubyPistolV2::FireLeft() {
	bool leftHand = playerPawnClass->GetLeftHand();

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, nameOfHand);

	if (GEngine && leftHand) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun in hand");
		if (nameOfHand == TEXT("LeftController")) {
			if (ammoClip > 0) {
				ShootingRaycast();
				PlayGunShotAudio();
				RemoveAmmo();
			}
			else if (ammoClip == 0) {
				if (pistolClickSound->IsValidLowLevelFast()) {
					pistolAudioComponent->SetSound(pistolClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && leftHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void ARubyPistolV2::FireRight() {
	bool rightHand = playerPawnClass->GetRightHand();

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, nameOfHand);

	if (GEngine && rightHand) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun in hand");
		if (nameOfHand == TEXT("RightController")) {
			if (ammoClip > 0) {
				ShootingRaycast();
				PlayGunShotAudio();
				RemoveAmmo();

			}
			else if (ammoClip == 0) {
				if (pistolClickSound->IsValidLowLevelFast()) {
					pistolAudioComponent->SetSound(pistolClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && rightHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void ARubyPistolV2::ShootingRaycast() {

	FHitResult* hitResult = new FHitResult();
	FVector startingPos = firingMeshPos->GetComponentLocation();
	FVector forwardVector = firingMeshPos->GetForwardVector();
	FVector endPos = ((forwardVector * 10000) + startingPos);
	FCollisionQueryParams* traceParams = new FCollisionQueryParams;


	if (GetWorld()->LineTraceSingleByChannel(*hitResult, startingPos, endPos, ECC_Visibility, *traceParams))
	{
		DrawDebugLine(GetWorld(), startingPos, endPos, FColor(255, 0, 0), true);

		ACharacter* actorHit = Cast<ACharacter>(hitResult->GetActor());

		enemySoldier = Cast<AGermanSoldier>(actorHit);
		enemyMedic = Cast<AGermanMedicV2>(actorHit);

		if (enemySoldier) {
			enemySoldier->TakeDamage(20);
		}

		if (enemyMedic) {
			enemyMedic->TakeDamage(20);
		}
	}

}

void ARubyPistolV2::Reload() {
	ammoClip = 8;
	if (pistolReloadSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolReloadSound);
	}
	PlayGunShotAudio();
}

void ARubyPistolV2::RemoveAmmo() {

	if (pistolShotSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolShotSound);
	}

	ammoClip--;
}

//Get Functions

bool ARubyPistolV2::GetPickedUp() {
	return pickedUp;
}

int ARubyPistolV2::GetAmmoClip() {
	return ammoClip;
}

void ARubyPistolV2::PlayGunShotAudio() {
	pistolAudioComponent->Play();
	
}
