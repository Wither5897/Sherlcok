// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Jin/AJH_EditorToolWidget.h"

// Sets default values
AAJH_EditorCharacter::AAJH_EditorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAJH_EditorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	pc = Cast<APlayerController>(Controller);
	if ( pc )
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if ( subSys )
		{
			subSys->AddMappingContext(IMC_EditorTool, 0);
		}
		pc->SetInputMode(FInputModeGameAndUI());
		pc->bShowMouseCursor = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}

	EditorWidget = Cast<UAJH_EditorToolWidget>(CreateWidget(GetWorld(), EditorWidgetFactory));
	if ( EditorWidget )
	{
		EditorWidget->AddToViewport();
	}

}

// Called every frame
void AAJH_EditorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform t = FTransform(GetControlRotation());
	direction = t.TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;


}

// Called to bind functionality to input
void AAJH_EditorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if ( input )
	{
		input->BindAction(IA_LookMouse, ETriggerEvent::Triggered, this, &AAJH_EditorCharacter::OnMyIA_LookMouse);
		input->BindAction(IA_EditorMove, ETriggerEvent::Triggered, this, &AAJH_EditorCharacter::OnMyIA_EditorMove);
		input->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_LeftClick);
		input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_RightClick);
	}

}

void AAJH_EditorCharacter::OnMyIA_LookMouse(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();
	AddControllerYawInput(v.X);
	AddControllerPitchInput(-v.Y);
}

void AAJH_EditorCharacter::OnMyIA_EditorMove(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();
	direction.X = v.X;
	direction.Y = v.Y;
}

void AAJH_EditorCharacter::OnMyIA_LeftClick()
{
	pc->SetShowMouseCursor(true);
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	pc->SetInputMode(InputMode);
}

void AAJH_EditorCharacter::OnMyIA_RightClick()
{
	//pc->SetShowMouseCursor(true);
	//pc->SetInputMode(FInputModeGameOnly());
}

