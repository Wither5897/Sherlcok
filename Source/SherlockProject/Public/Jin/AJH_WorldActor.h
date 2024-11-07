// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_WorldActor.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_WorldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_WorldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* X_Axis;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Y_Axis;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Z_Axis;


	UFUNCTION()
	void ResetVisibility();

	UPROPERTY()
	bool bIsWorldSpawn = false;
	bool bIsAxisLocation = false;
};
