// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_CreatorToolTravelActor.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_CreatorToolTravelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_CreatorToolTravelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* TravelboxComp;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* player;
	UPROPERTY()
	class ASherlockPlayerController* pc;

	UFUNCTION()
	void OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMyEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
