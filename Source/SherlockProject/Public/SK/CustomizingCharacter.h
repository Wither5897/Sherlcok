// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomizingCharacter.generated.h"

UCLASS()
class SHERLOCKPROJECT_API ACustomizingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomizingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* CoatMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* HatMesh;
	
	UFUNCTION()
	void SetCoatMaterial(class UMaterial* Material);

	UFUNCTION()
	void SetHatMaterial(class UMaterial* Material);

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> LoadingUIFactory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UUserWidget* LoadingUI;
};
