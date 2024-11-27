// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AJH_Sun.generated.h"

UCLASS()
class SHERLOCKPROJECT_API AAJH_Sun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_Sun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Override settings", meta = (ClampMin = "-1.0", ClampMax = "1.0", SliderMin = "-1.0", SliderMax = "1.0"))
	float height_Sun = 0.33;

	UFUNCTION(BlueprintNativeEvent)
	void RefreshMateiral(float Height);
};
