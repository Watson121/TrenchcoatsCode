// Fill out your copyright notice in the Description page of Project Settings.

#include "GermanSoldier.h"


// Sets default values
AGermanSoldier::AGermanSoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 100;
}

// Called when the game starts or when spawned
void AGermanSoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGermanSoldier::Tick(float DeltaTime)
{
	//if (health <= 0) {
	//	Destroy(this);
	//}

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGermanSoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGermanSoldier::TakeDamage(int damage) {
	health = health - damage;
}



