// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Jin/AJH_EditorToolWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorActor.h"
#include "Jin/AJH_WorldActor.h"

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

	EditorActor = Cast<AAJH_EditorActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorActor::StaticClass()));
	WorldActor = Cast<AAJH_WorldActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_WorldActor::StaticClass()));
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

	if ( bIsActorSpawn && EditorActor != nullptr )
	{
		GetWorld()->SpawnActor<AAJH_WorldActor>(WorldActorFactory, EditorActor->GetActorTransform());
		EditorActor->bIsSpawn = false;
		EditorActor->Destroy();
		bIsEditorActor = false;
	}
	else
	{
		return;
	}
}

void AAJH_EditorCharacter::OnMyIA_RightClick()
{
	
}

void AAJH_EditorCharacter::OnMyEditorActorSpawn(bool bIsSpawn, int32 num)
{
	// 새로운 액터 스폰
	if ( bIsSpawn)
	{
		pc->GetHitResultUnderCursorByChannel(query, true, outHit);
		FTransform transform(outHit.Location);
		EditorActor = GetWorld()->SpawnActor<AAJH_EditorActor>(EditorActorFactory, transform);
		EditorActor->OnMyMeshPath(num);
		EditorActor->bIsSpawn = true;
		bIsActorSpawn = true;
		bIsEditorActor = true;
	}
	else
	{
		bIsEditorActor = false;
		EditorActor->Destroy();
	}
}

