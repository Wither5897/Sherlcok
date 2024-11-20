// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_LobbyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AAJH_LobbyPawn::AAJH_LobbyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAJH_LobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if ( pc )
	{
		FInputModeGameAndUI InputMode;
		pc->SetInputMode(InputMode);
		pc->bShowMouseCursor = true;
	}

}

// Called every frame
void AAJH_LobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAJH_LobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

