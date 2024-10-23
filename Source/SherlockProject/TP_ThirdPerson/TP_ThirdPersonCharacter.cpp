// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EvidenceActor.h"
#include "KHH_InteractionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "SK/InventoryWidget.h"
#include "SK/EvidenceActorComp.h"
#include "SK/ItemWidget.h"
#include "SK/NoteItemWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Arrow, ChildActor
	//EvidenceArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("EvidenceArrow"));
	//EvidenceArrow->SetupAttachment(FollowCamera);
	//EvidenceArrow->ArrowLength = 22;
	//EvidenceArrow->SetRelativeLocation(FVector( 0, -35, 0 ));

	//ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	//ChildActor->SetupAttachment(FollowCamera);
	//ChildActor->SetRelativeLocation(FVector(70, 0, 0));
	//ChildActor->SetChildActorClass(EvidenceActor);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//PlayerController = Cast<APlayerController>(GetController());

	//ChildActor->SetVisibility(false);

	interactionUI = CreateWidget<UKHH_InteractionWidget>(GetWorld(), interactionUIsetting);
	//EvidenceActor = Cast<AEvidenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvidenceActor::StaticClass()));

	if ( interactionUI )
	{
		interactionUI->AddToViewport();
		interactionUI->SetVisibility(ESlateVisibility::Hidden);
	}

	InventoryUI = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryUIFactory));
	if ( InventoryUI ) {
		InventoryUI->AddToViewport();
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ATP_ThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowCamera->FieldOfView = FMath::Lerp(FollowCamera->FieldOfView, TargetFOV, DeltaTime * 5);
	
	PerformLineTrace();
	PerformHighLight();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if ( APlayerController* PlayerController = Cast<APlayerController>(GetController()) )
	{
		if ( UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) )
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if ( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) ) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Look);


		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::OnMyActionZoomIn);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &ATP_ThirdPersonCharacter::OnMyActionZoomOut);

		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::Interaction);

		EnhancedInputComponent->BindAction(IA_OpenInventory, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::OpenInventory);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if ( Controller != nullptr )
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATP_ThirdPersonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if ( Controller != nullptr )
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATP_ThirdPersonCharacter::OnMyActionZoomIn()
{
	TargetFOV = 60;
}

void ATP_ThirdPersonCharacter::OnMyActionZoomOut()
{
	TargetFOV = 90;
}

void ATP_ThirdPersonCharacter::HighlightActor()
{
	if ( EvidenceActor && EvidenceActor->StaticMesh )
	{
		EvidenceActor->StaticMesh->SetRenderCustomDepth(true);
		EvidenceActor->StaticMesh->SetCustomDepthStencilValue(2);
	}
}

void ATP_ThirdPersonCharacter::UnHighlightActor()
{
	if ( EvidenceActor && EvidenceActor->StaticMesh )
	{
		EvidenceActor->StaticMesh->SetRenderCustomDepth(false);
	}
}

void ATP_ThirdPersonCharacter::PerformHighLight()
{
	if ( bHit )
	{
		EvidenceActor = Cast<AEvidenceActor>(OutHit.GetActor());

		if ( EvidenceActor && OutHit.GetActor()->ActorHasTag(TEXT("InteractObj")) )
		{
			HighlightActor();
		}
		else
		{
			UnHighlightActor();
		}
	}
	else
	{
		UnHighlightActor();
	}
}

void ATP_ThirdPersonCharacter::Interaction()
{
	auto* pc = Cast<APlayerController>(GetController());
	//PerformLineTrace();
	if ( !interactionUI ) {
		return;
	}
	if ( !pc ) {
		return;
	}
	if ( bHit && OutHit.GetActor()->ActorHasTag(TEXT("InteractObj")) ){
		AEvidenceActor* actor = Cast<AEvidenceActor>(OutHit.GetActor());
		if ( !bPick ){
			interactionUI->SetVisibility(ESlateVisibility::Visible);
			if ( !actor->Comp ) {
				return;
			}
			int32 actorNum = actor->Comp->GetTagNum();
			InventoryUI->ItemArray[actorNum - 1]->WhenFindItem();
			InventoryUI->NoteItemArray[actorNum - 1]->WhenFindItem();

			interactionUI->InteractionWidgetSwitcher->SetActiveWidgetIndex(actorNum - 1);

			pc->SetShowMouseCursor(true);
			pc->SetInputMode(FInputModeGameAndUI());
			GetCharacterMovement()->DisableMovement();
		}
		else{
			interactionUI->SetVisibility(ESlateVisibility::Hidden);
			pc->SetShowMouseCursor(false);
			pc->SetInputMode(FInputModeGameOnly());
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
		bPick = !bPick;
	}
}

void ATP_ThirdPersonCharacter::PerformLineTrace()
{
	start = FollowCamera->GetComponentLocation();
	End = start + FollowCamera->GetForwardVector() * tracedis;
	traceChannel = ECC_Visibility;
	Params;
	Params.AddIgnoredActor(this);

	bHit = GetWorld()->LineTraceSingleByChannel(OutHit, start, End, traceChannel, Params);

	DrawDebugLine(GetWorld(), start, End, bHit ? FColor::Green : FColor::Red, false, 2.0f, 0, 1.0f);
}

void ATP_ThirdPersonCharacter::OpenInventory()
{
	auto* pc = Cast<APlayerController>(GetController());
	if ( !pc ) {
		return;
	}
	if ( InventoryUI->IsVisible() ) {
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		pc->SetShowMouseCursor(false);
		pc->SetInputMode(FInputModeGameOnly());
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else {
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeGameAndUI());
		GetCharacterMovement()->DisableMovement();
	}
}

