// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorToolPawn.h"
#include "GameFramework/PlayerController.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

AAJH_EditorToolPawn::AAJH_EditorToolPawn()
{
	PrimaryActorTick.bCanEverTick = true;


}

void AAJH_EditorToolPawn::BeginPlay()
{
	Super::BeginPlay();

	pc = Cast<APlayerController>(Controller);
	if(pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if ( subSys )
		{
			subSys->AddMappingContext(IMC_EditorTool, 0);
		}
		pc->SetInputMode(FInputModeGameAndUI());
		pc->SetShowMouseCursor(true);
	}

}

void AAJH_EditorToolPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAJH_EditorToolPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if ( input )
	{
		input->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AAJH_EditorToolPawn::OnMyIA_LeftClick);
		input->BindAction(IA_LeftClick, ETriggerEvent::Canceled, this, &AAJH_EditorToolPawn::OnMyMouseActionCanceled);
		input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &AAJH_EditorToolPawn::OnMyIA_RightClick);
		input->BindAction(IA_RightClick, ETriggerEvent::Canceled, this, &AAJH_EditorToolPawn::OnMyMouseActionCanceled);
	}
}

void AAJH_EditorToolPawn::OnMyIA_LeftClick()
{
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());
	UE_LOG(LogTemp, Warning, TEXT("11111"));
}

void AAJH_EditorToolPawn::OnMyIA_RightClick()
{
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());
}

void AAJH_EditorToolPawn::OnMyMouseActionCanceled()
{
	pc->SetShowMouseCursor(true);
	pc->SetInputMode(FInputModeGameAndUI());
	UE_LOG(LogTemp, Warning, TEXT("11111"));
}
