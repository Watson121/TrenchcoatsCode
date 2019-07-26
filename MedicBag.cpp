// Fill out your copyright notice in the Description page of Project Settings.

#include "MedicBag.h"
#include "PlayerPawn.h"



// Sets default values
AMedicBag::AMedicBag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	medicBagMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Medic Bag"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> medicBagMeshObject(TEXT("StaticMesh'/Game/Assets/Models/MedicBag.MedicBag'"));
	medicBagMesh = medicBagMeshObject.Object;

	if (medicBagMesh) {
		medicBagMeshComponent->SetStaticMesh(medicBagMesh);
	}

	RootComponent = medicBagMeshComponent;
}

// Called when the game starts or when spawned
void AMedicBag::BeginPlay()
{
	for (TActorIterator<APlayerPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		playerPawn = *ActorItr;
	}

	Super::BeginPlay();
}

// Called every frame
void AMedicBag::Tick(float DeltaTime)
{
	if (pickedUp) {
		playerPawn->SetMedicBag(this);
	}

	Super::Tick(DeltaTime);
}

void AMedicBag::DestroyThis() {
	Destroy(this);
}



