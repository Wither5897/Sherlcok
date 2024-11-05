// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_EditorActor.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_EditorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_EditorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	APlayerController* pc;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;
	const TCHAR* MeshPath;
	UStaticMesh* LoadeMesh;

	UPROPERTY()
	bool bIsSpawn = false;

	UFUNCTION()
	void OnMyMeshPath(int32 Itemnumber);
};
