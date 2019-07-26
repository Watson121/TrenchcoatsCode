// Fill out your copyright notice in the Description page of Project Settings.

#include "FrenchRifle.h"
#include "PlayerPawn.h"
#include "GermanMedicV2.h"
#include "GermanSoldier.h"



// Sets default values
AFrenchRifle::AFrenchRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


//This sets up all of the meshes for the rifle 
#pragma region SETTING UP THE MESHES

	rifleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rifle Mesh"));
	firingMeshPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front of Gun"));
	firingMeshPos->SetupAttachment(rifleMesh);

	firingMeshPos->SetRelativeLocation(FVector(93.0f, 1.9f, 6.7f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> rifleMeshObject(TEXT("StaticMesh'/Game/Assets/Models/RifleUVNEW.RifleUVNEW'"));
	rifle = rifleMeshObject.Object;

	if (rifle) {
		rifleMesh->SetStaticMesh(rifle);
	}

#pragma endregion

#pragma region SETTING UP THE AUDIO
	static ConstructorHelpers::FObjectFinder<USoundWave> rifleShot(TEXT("SoundWave'/Game/Assets/Audio/BOLRIF.BOLRIF'"));
	rifleShotSound = rifleShot.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> rifleReload(TEXT("SoundWave'/Game/Assets/Audio/BOLT.BOLT'"));
	rifleReloadSound = rifleReload.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> rifleClick(TEXT("SoundWave'/Game/Assets/Audio/Pistol_Hammer_Cock_02.Pistol_Hammer_Cock_02'"));
	rifleClickSound = rifleClick.Object;

	rifleAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RifleAudioComponent"));
	rifleAudioComponent->bAutoActivate = false;

	if (rifleShotSound->IsValidLowLevelFast()) {
		rifleAudioComponent->SetSound(rifleShotSound);
	}
#pragma endregion

#pragma region SETTING UP PARTICLE EFFECTS

	static ConstructorHelpers::FObjectFinder<UParticleSystem> rifleFire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_MuzzleFlash.P_MuzzleFlash'"));
	muzzleFlashParticle = rifleFire.Object;

	rifleParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RifleParticleSystem"));
	rifleParticleSystem->bAutoActivate = false;

	if (muzzleFlashParticle->IsValidLowLevelFast()) {
		rifleParticleSystem->SetTemplate(muzzleFlashParticle);
	}

	

#pragma endregion

	World = GetWorld();

}

// Called when the game starts or when spawned
void AFrenchRifle::BeginPlay()
{

	for (TActorIterator<APlayerPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		playerPawnClass = *ActorItr;
	}

	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ammoClip = 5;


	Super::BeginPlay();
	
}

// Called every frame
void AFrenchRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region FUNCTIONS RELATED TO SHOOTING THE RIFLE

void AFrenchRifle::FireLeft() {
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
				if (rifleClickSound->IsValidLowLevelFast()) {
					rifleAudioComponent->SetSound(rifleClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && leftHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void AFrenchRifle::FireRight() {
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
				if (rifleClickSound->IsValidLowLevelFast()) {
					rifleAudioComponent->SetSound(rifleClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && rightHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void AFrenchRifle::ShootingRaycast() {
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
			enemySoldier->TakeDamage(40);
		}

		if (enemyMedic) {
			enemyMedic->TakeDamage(40);
		}
	}
}

void AFrenchRifle::RemoveAmmo() {
	if (rifleShotSound->IsValidLowLevelFast()) {
		rifleAudioComponent->SetSound(rifleShotSound);
	}

	ammoClip--;
}

#pragma endregion

void AFrenchRifle::Reload() {
	ammoClip = 5;
	if (rifleReloadSound->IsValidLowLevelFast()) {
		rifleAudioComponent->SetSound(rifleReloadSound);
	}
	PlayGunShotAudio();
}

void AFrenchRifle::PlayGunShotAudio() {
	rifleAudioComponent->Play();
}


#pragma region GETTER FUNCTIONS

bool AFrenchRifle::GetPickedUp() {
	return pickedUp;
}

int AFrenchRifle::GetAmmoClip() {
	return ammoClip;
}

#pragma endregion




