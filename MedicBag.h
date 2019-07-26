// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MedicBag.generated.h"

class APlayerPawn;

UCLASS()
class TRENCHCOATSGAME_API AMedicBag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMedicBag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyThis();
	
#pragma region STATIC MESHES

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* medicBagMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMesh* medicBagMesh;

#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool pickedUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		APlayerPawn* playerPawn;

};
