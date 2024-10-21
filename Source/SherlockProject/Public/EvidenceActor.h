// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HighLightInterface.h"
#include "EvidenceActor.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AEvidenceActor : public AActor, public IHighLightInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEvidenceActor();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	APlayerController* PlayerController;

	//void PerformLineTrace();

	float TraceDistance = 200;

};
