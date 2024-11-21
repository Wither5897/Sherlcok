// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_DirectionalLight.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_DirectionalLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_DirectionalLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Directional Light 컴포넌트
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Light")
    class UDirectionalLightComponent* directionalLightComp;

};
