// Fill out your copyright notice in the Description page of Project Settings.

#include "GermanMedicV2.h"


// Sets default values
AGermanMedicV2::AGermanMedicV2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 100;
}

// Called when the game starts or when spawned
void AGermanMedicV2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGermanMedicV2::Tick(float DeltaTime)
{
	//if (health <= 0) {
	//	Destroy(this);
	//}
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGermanMedicV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGermanMedicV2::TakeDamage(int damage) {
	health = health - damage;
}

