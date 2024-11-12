// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/AnimPawn.h"

// Sets default values
AAnimPawn::AAnimPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
}

// Called every frame
void AAnimPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

