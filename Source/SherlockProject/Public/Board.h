// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UW_ReportBoard.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Board.generated.h"

UCLASS()
class SHERLOCKPROJECT_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetVisibleBoard();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UBoxComponent* BoxArea;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UWidgetComponent* WidgetReportBoard;

	UPROPERTY(BlueprintReadWrite)
	class ATP_ThirdPersonCharacter* me;

	UPROPERTY(BlueprintReadWrite)
	class UUW_ReportBoard* reportboard;

};
