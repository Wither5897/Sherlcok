﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_MainTravelActor.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_MainTravelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_MainTravelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySetting)
	class UBoxComponent* mainTravelBoxComp;

	UPROPERTY()
	class ATP_ThirdPersonCharacter* player;
	UPROPERTY()
	class ASherlockPlayerController* pc;

	UPROPERTY()
	class UAJH_CrimeSceneTravelWidget* CrimeSceneTravelWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> CrimeSceneTravelWidgetFactory;
	UPROPERTY()
	class UAJH_TravelClientWidget* TravelClientWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> TravelClientWidgetFactory;
	

	UFUNCTION()
	void ShowCrimeSceneTravelWidget_Server(AActor* OtherActor);
	UFUNCTION()
	void ShowCrimeSceneTravelWidget_Client(AActor* OtherActor);

	UFUNCTION()
	void OnMyMainTravelBoxBeginClick(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMyMainTravelBoxEndClick(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void OnMyMainTravelBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMyMainTravelBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
