// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"

#include "AJH_SherlockGameInstance.h"
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
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SK/InventoryWidget.h"
#include "SK/EvidenceActorComp.h"
#include "SK/ItemWidget.h"
#include "SK/HighlightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerState.h"
#include "UW_ReportBoard.h"
// #include "Editor/GroupActor.h"
#include "GameFramework/GameStateBase.h"
#include "Jin/AJH_SummaryWidget.h"
#include "SK/StatisticsWidget.h"
#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Jin/AJH_TravelClientWidget.h"
#include "SK/NoteItemWidget.h"

// 에디터 전용 코드 분리
#if WITH_EDITOR
#include "Editor/GroupActor.h"
// 에디터 전용 작업 수행
#endif
#include "LevelSequencePlayer.h"
#include "TP_ThirdPersonGameMode.h"
#include "Sound/SoundWave.h"
#include "UObject/ConstructorHelpers.h"
#include "Jin/AJH_CreatorToolTravel.h"
#include "SK/AnimPawn.h"
#include "UW_EndingCredit.h"
#include "SK/EditIntroPlayWidget.h"
#include "SK/EditOutroPlayWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter(){
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bReplicates = true;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
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
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(FollowCamera);
	SpotLight->SetRelativeRotation(FRotator(10.0f, 0.0f, 0.0f));
	SpotLight->Intensity = 5000.f;
	SpotLight->AttenuationRadius = 2500.f;
	SpotLight->InnerConeAngle = 20.f;
	SpotLight->SetVisibility(false);

	CoatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoatMesh"));
	CoatMesh->SetupAttachment(GetMesh());

	HatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatMesh"));
	HatMesh->SetupAttachment(GetMesh(), TEXT("hatSocket"));
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Comp = CreateDefaultSubobject<UHighlightComponent>(TEXT("HighlighComp"));



	ConstructorHelpers::FObjectFinder<USoundWave> MainSoundObj(TEXT("/Game/KHH/Sound/Main_scene.Main_scene"));
	if ( MainSoundObj.Succeeded() )
	{
		MainSound = MainSoundObj.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundWave> CaseSoundObj(TEXT("/Game/KHH/Sound/Incident_scene.Incident_scene"));
	if ( CaseSoundObj.Succeeded() )
	{
		CaseSound = CaseSoundObj.Object;
	}

	EvidenceSound = LoadObject<USoundWave>(nullptr, TEXT("/Game/KHH/Sound/Interaction_sound/Camera_shutter_click.Camera_shutter_click"));
	PaperSound = LoadObject<USoundWave>(nullptr, TEXT("/Game/KHH/Sound/Interaction_sound/paper.paper"));
}

void ATP_ThirdPersonCharacter::BeginPlay(){
	// Call the base class  
	Super::BeginPlay();

	//PlayerController = Cast<APlayerController>(GetController());

	//ChildActor->SetVisibility(false);

	interactionUI = CreateWidget<UKHH_InteractionWidget>(GetWorld(), interactionUIsetting);
	//EvidenceActor = Cast<AEvidenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvidenceActor::StaticClass()));

	if (interactionUI){
		interactionUI->AddToViewport();
		interactionUI->SetVisibility(ESlateVisibility::Hidden);
	}

	InventoryUI = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryUIFactory));
	if (InventoryUI){
		InventoryUI->AddToViewport();
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}

	Notify = Cast<UUW_Notify>(CreateWidget(GetWorld(), NotifyUI));
	if (Notify){
		Notify->AddToViewport();
		Notify->SetVisibility(ESlateVisibility::Hidden);
	}
	
	reportboard = Cast<UUW_ReportBoard>(CreateWidget(GetWorld(), reportboardUI));
	if (reportboard){
		reportboard->AddToViewport();
		reportboard->SetVisibility(ESlateVisibility::Hidden);
	}

	SummaryWidget = Cast<UAJH_SummaryWidget>(CreateWidget(GetWorld(), SummaryWidgetFactory));
	if (SummaryWidget){
		SummaryWidget->AddToViewport();
		SummaryWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	CrimeSceneTravelWidget = Cast<UAJH_CrimeSceneTravelWidget>(CreateWidget(GetWorld(), CrimeSceneTravelWidgetFactory));
	if (CrimeSceneTravelWidget){
		CrimeSceneTravelWidget->AddToViewport();
		CrimeSceneTravelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	TravelClientWidget = Cast<UAJH_TravelClientWidget>(CreateWidget(GetWorld(), TravelClientWidgetFactory));
	if (TravelClientWidget){
		TravelClientWidget->AddToViewport();
		TravelClientWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	CreatorToolTravel = Cast<UAJH_CreatorToolTravel>(CreateWidget(GetWorld(), CreatorToolTravelFactory));
	if ( CreatorToolTravel )
	{
		CreatorToolTravel->AddToViewport();
		CreatorToolTravel->SetVisibility(ESlateVisibility::Collapsed);
	}

	StatisticsUI = Cast<UStatisticsWidget>(CreateWidget(GetWorld(), StatisticsUIFactory));
	if (StatisticsUI){
		StatisticsUI->AddToViewport();
		StatisticsUI->SetVisibility(ESlateVisibility::Hidden);
	}
	
	LoadingUI = Cast<UUserWidget>(CreateWidget(GetWorld(), LoadingUIFactory));
	if(LoadingUI){
		LoadingUI->AddToViewport();
		LoadingUI->SetVisibility(ESlateVisibility::Hidden);
	}

	OutroUI = Cast<UUW_EndingCredit>(CreateWidget(GetWorld(), OutroUIFactory));
	if ( OutroUI ) {
		OutroUI->AddToViewport();
		OutroUI->SetVisibility(ESlateVisibility::Hidden);
	}
	
	EditIntroUI = Cast<UEditIntroPlayWidget>(CreateWidget(GetWorld(), EditIntroUIFactory));
	if (EditIntroUI){
		EditIntroUI->AddToViewport();
		EditIntroUI->SetVisibility(ESlateVisibility::Visible);
	}

	// 이건 나중에 특정한 위치에서 만들어야함
	EditOutroUI = Cast<UEditOutroPlayWidget>(CreateWidget(GetWorld(), EditOutroUIFactory));
	if (EditOutroUI){
		EditOutroUI->AddToViewport();
		EditOutroUI->SetVisibility(ESlateVisibility::Hidden);
	}

	gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	ps = GetPlayerState();
	
	if(HasAuthority()){
		if(ps){
			int32 PlayerIndex = ps->GetPlayerId();
			ServerSetCharacterMaterial(PlayerIndex);
		}
	}
	
	// ServerSetCharacterMaterial(ps->GetPlayerId());
}

void ATP_ThirdPersonCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	FollowCamera->FieldOfView = FMath::Lerp(FollowCamera->FieldOfView, TargetFOV, DeltaTime * 5);

	PerformLineTrace();
	PerformHighLight();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Look);


		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Started, this,
		                                   &ATP_ThirdPersonCharacter::OnMyActionZoomIn);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Completed, this,
		                                   &ATP_ThirdPersonCharacter::OnMyActionZoomOut);

		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Started, this,
		                                   &ATP_ThirdPersonCharacter::Interaction);

		EnhancedInputComponent->BindAction(IA_OpenInventory, ETriggerEvent::Started, this,
		                                   &ATP_ThirdPersonCharacter::OpenInventory);

		EnhancedInputComponent->BindAction(IA_FlashLight, ETriggerEvent::Started, this,
		                                   &ATP_ThirdPersonCharacter::OnOffFlashLight);
	}
	else{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value){
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr){
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

void ATP_ThirdPersonCharacter::Look(const FInputActionValue& Value){
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr){
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * 0.7);
		AddControllerPitchInput(LookAxisVector.Y * 0.7);
	}
}

void ATP_ThirdPersonCharacter::OnMyActionZoomIn(){
	TargetFOV = 60;
}

void ATP_ThirdPersonCharacter::OnMyActionZoomOut(){
	TargetFOV = 90;
}

void ATP_ThirdPersonCharacter::OnOffFlashLight(){
	if (SpotLight->GetVisibleFlag()){
		SpotLight->SetVisibility(false);
	}
	else{
		SpotLight->SetVisibility(true);
	}
}

void ATP_ThirdPersonCharacter::PerformHighLight(){
	if (IsLocallyControlled()){
		if (Comp){
			// 이전에 하이라이트된 오브젝트의 하이라이트를 해제
			if (EvidenceActor && EvidenceActor->StaticMesh){
				Comp->SKUnHighlight(OutputMeshComp);
			}

			if (bHit){
				AActor* HitActor = OutHit.GetActor();
				if (HitActor) // Actor가 nullptr이 아닌지 확인
				{
					EvidenceActor = Cast<AEvidenceActor>(HitActor);
					if (EvidenceActor){
						EvidenceActor->GetComponents<UStaticMeshComponent>(OutputMeshComp);

						// OutputMeshComp가 비어있지 않고, InteractObj 태그를 가진 경우
						if (EvidenceActor->ActorHasTag(TEXT("InteractObj")) && OutputMeshComp.Num() > 0){
							Comp->SKHighlight(OutputMeshComp);
						}
						else{
							Comp->SKUnHighlight(OutputMeshComp);
						}
					}
				}
			}
			else{
				Comp->SKUnHighlight(OutputMeshComp);
			}
		}
	}
}

void ATP_ThirdPersonCharacter::Interaction(){
    auto* pc = Cast<APlayerController>(GetController());
    if (!interactionUI || !pc){
        return;
    }
    if (bHit && OutHit.GetActor()->ActorHasTag(TEXT("InteractObj"))){
        AEvidenceActor* actor = Cast<AEvidenceActor>(OutHit.GetActor());
        if (!actor){
            return;
        }
    	if (!ps){
    		ps = GetPlayerState();
    	}
        if (!bPick){
            int32 actorNum = actor->Comp->GetTagNum();
            int32 playerId = ps->GetPlayerId();
        	if(HasAuthority()){
        		MulticastItemFound(actorNum, playerId);
        	}
        	else{
        		ServerItemFound(actorNum, playerId);
        	}
        	
            if (InventoryUI && InventoryUI->NoteItemArray.IsValidIndex((actorNum - 1))) {
                InventoryUI->NoteItemArray[actorNum - 1]->WhenFindItem();
            }

            interactionUI->SetVisibility(ESlateVisibility::Visible);
            interactionUI->WhenItemClick(actorNum);
            PlayEvidenceSound();
            pc->SetShowMouseCursor(true);
            pc->SetInputMode(FInputModeGameAndUI());
            GetCharacterMovement()->DisableMovement();
        }
        else {
            // UI가 닫힐 때 실행
            interactionUI->SetVisibility(ESlateVisibility::Hidden);
            pc->SetShowMouseCursor(false);
            pc->SetInputMode(FInputModeGameOnly());
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);

            // UI가 닫힌 후 조건에 따라 레벨 시퀀스 실행
            if (check[3] && check[5] && check[8] && !bSequence) {
                FMovieSceneSequencePlaybackSettings PlaybackSettings;
                ALevelSequenceActor* OutActor;
                ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
                    GetWorld(), LevelSequence, PlaybackSettings, OutActor);
                
                if (LevelSequencePlayer) {
                    AnimPawn = Cast<AAnimPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AAnimPawn::StaticClass()));
                    if(AnimPawn) {
                        AnimPawn->SetActorHiddenInGame(false);
                    }
                    LevelSequencePlayer->OnFinished.AddDynamic(this, &ATP_ThirdPersonCharacter::SetAnimPawnVisibility);
                    LevelSequencePlayer->Play();
                }
                bSequence = true;
            }
        }
        bPick = !bPick;
    }
}

void ATP_ThirdPersonCharacter::SetAnimPawnVisibility(){
	AnimPawn->SetActorHiddenInGame(true);
}

void ATP_ThirdPersonCharacter::UpdatePlayerCollectionPercentage(){
	auto* GS = GetWorld()->GetGameState();
	if (!GS) return;

	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	if (UAJH_SherlockGameInstance* MyGI = Cast<UAJH_SherlockGameInstance>(GI))
	{
		// PlayerCollection 초기화
		MyGI->PlayerCollection.Init(0.0f, 3);

		for (APlayerState* PS : GS->PlayerArray)
		{
			// 각 플레이어의 Pawns를 가져옴
			if (ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(PS->GetPawn()))
			{
				if (!Player->InventoryUI) continue;

				// 각 플레이어의 아이템 상태 계산
				int32 TotalItems = 9; // 전체 아이템 개수
				int32 CollectedItems = 0;

				for (auto* Item : Player->InventoryUI->ItemArray)
				{
					if (Item && !Item->QuestionMark->IsVisible())
					{
						CollectedItems++;
					}
				}

				// 퍼센티지 계산
				int32 PlayerID = Player->GetPlayerState()->GetPlayerId();
				float CollectionPercentage = (TotalItems > 0) 
					? (static_cast<float>(CollectedItems) / TotalItems) * 100.0f 
					: 0.0f;

				// 게임 인스턴스의 배열 갱신
				if (MyGI->PlayerCollection.IsValidIndex(PlayerID))
				{
					MyGI->PlayerCollection[PlayerID] = CollectionPercentage;
				}
			}
		}
	}

	// UI 업데이트 호출
	UpdateAllPlayerCollections();
}

void ATP_ThirdPersonCharacter::UpdateAllPlayerCollections_Implementation(){
	auto* GS = GetWorld()->GetGameState();
	if (!GS) return;

	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	if (UAJH_SherlockGameInstance* MyGI = Cast<UAJH_SherlockGameInstance>(GI))
	{
		for (APlayerState* PS : GS->PlayerArray)
		{
			if (ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(PS->GetPawn()))
			{
				if (!Player->InventoryUI) continue;

				// UI 텍스트 업데이트
				Player->InventoryUI->Player1CollectionText->SetText(
					FText::FromString(FString::Printf(TEXT("%.0f%%"), MyGI->PlayerCollection[0])));
				Player->InventoryUI->Player2CollectionText->SetText(
					FText::FromString(FString::Printf(TEXT("%.0f%%"), MyGI->PlayerCollection[1])));
				Player->InventoryUI->Player3CollectionText->SetText(
					FText::FromString(FString::Printf(TEXT("%.0f%%"), MyGI->PlayerCollection[2])));
			}
		}
	}
}

void ATP_ThirdPersonCharacter::ItemFound(int32 ActorNum, int32 PlayerID){
	InventoryUI->ItemArray[ActorNum - 1]->QuestionMark->SetVisibility(ESlateVisibility::Hidden);
	
	auto* gs = GetWorld()->GetGameState();
	TArray<APlayerState*> PlayerArray = gs->PlayerArray;

	for (APlayerState* ps2 : PlayerArray){
		if (ATP_ThirdPersonCharacter* Character = Cast<ATP_ThirdPersonCharacter>(ps2->GetPawn())){
			if (Character->InventoryUI && Character->InventoryUI->ItemArray.IsValidIndex(ActorNum - 1)){
				switch (PlayerID){
				case 0:
					Character->InventoryUI->ItemArray[ActorNum - 1]->Player1Light->SetVisibility(
						ESlateVisibility::Visible);
					break;
				case 1:
					Character->InventoryUI->ItemArray[ActorNum - 1]->Player2Light->SetVisibility(
						ESlateVisibility::Visible);
					break;
				case 2:
					Character->InventoryUI->ItemArray[ActorNum - 1]->Player3Light->SetVisibility(
						ESlateVisibility::Visible);
					break;
				default:
					break;
				}
				Character->UpdatePlayerCollectionPercentage();
			}
		}
	}
}

void ATP_ThirdPersonCharacter::ServerItemFound_Implementation(int32 ActorNum, int32 PlayerID){
	MulticastItemFound(ActorNum, PlayerID);
	// ItemFound(ActorNum, PlayerID);
}

void ATP_ThirdPersonCharacter::MulticastItemFound_Implementation(int32 ActorNum, int32 PlayerID){
	if (IsLocallyControlled()){
		if (InventoryUI && InventoryUI->ItemArray.IsValidIndex((ActorNum - 1))){
			InventoryUI->ItemArray[ActorNum - 1]->VisibleBoard();
		}
	}
	ItemFound(ActorNum, PlayerID);
}

void ATP_ThirdPersonCharacter::PerformLineTrace(){
	start = FollowCamera->GetComponentLocation();
	End = start + FollowCamera->GetForwardVector() * tracedis;
	traceChannel = ECC_Visibility;
	Params;
	Params.AddIgnoredActor(this);

	bHit = GetWorld()->LineTraceSingleByChannel(OutHit, start, End, traceChannel, Params);

	// DrawDebugLine(GetWorld(), start, End, bHit ? FColor::Green : FColor::Red, false, 2.0f, 0, 1.0f);
}

void ATP_ThirdPersonCharacter::OpenInventory(){
	auto* pc = Cast<APlayerController>(GetController());
	PlayInventorySound();
	if (!pc){
		return;
	}
	if (InventoryUI->IsVisible()){
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		pc->SetShowMouseCursor(false);
		pc->SetInputMode(FInputModeGameOnly());
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else{
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeGameAndUI());
		GetCharacterMovement()->DisableMovement();
		if(!ps){
			ps = GetPlayerState();
		}
		int32 playerId = ps->GetPlayerId();
		FWidgetTransform NewTransform;
		switch (playerId){
		case 0:
			NewTransform.Translation = FVector2D(0, 0);
			break;
		case 1:
			NewTransform.Translation = FVector2D(115, 0);
			break;
		case 2:
			NewTransform.Translation = FVector2D(230, 0);
			break;
		default:
			break;
		}
		InventoryUI->MyPlayerID->SetRenderTransform(NewTransform);
	}
}

void ATP_ThirdPersonCharacter::MainTravel(AActor* OtherActor){
	if (OtherActor){
		CrimeSceneTravelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATP_ThirdPersonCharacter::SetSummaryMulti(int32 Category, UTexture2D* SavedTexture, int32 PlayerID){
	auto* gs = GetWorld()->GetGameState();
	TArray<APlayerState*> PlayerArray = gs->PlayerArray;

	for (APlayerState* ps2 : PlayerArray){
		if (ATP_ThirdPersonCharacter* Character = Cast<ATP_ThirdPersonCharacter>(ps2->GetPawn())){
			if (!Character->SummaryWidget){
				return;
			}
			switch (Category){
			case 0:
				if (PlayerID == 0){
					Character->SummaryWidget->Img_SuspectImage1->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SuspectImage1->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 1){
					Character->SummaryWidget->Img_SuspectImage2->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SuspectImage2->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 2){
					Character->SummaryWidget->Img_SuspectImage3->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SuspectImage3->SetBrushFromTexture(SavedTexture);
				}
				break;
			case 1:
				if (PlayerID == 0){
					Character->SummaryWidget->Img_WeaponImage1->SetOpacity(1.0f);
					Character->SummaryWidget->Img_WeaponImage1->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 1){
					Character->SummaryWidget->Img_WeaponImage2->SetOpacity(1.0f);
					Character->SummaryWidget->Img_WeaponImage2->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 2){
					Character->SummaryWidget->Img_WeaponImage3->SetOpacity(1.0f);
					Character->SummaryWidget->Img_WeaponImage3->SetBrushFromTexture(SavedTexture);
				}
				break;
			case 2:
				if (PlayerID == 0){
					Character->SummaryWidget->Img_MainEvidenceImage1->SetOpacity(1.0f);
					Character->SummaryWidget->Img_MainEvidenceImage1->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 1){
					Character->SummaryWidget->Img_MainEvidenceImage2->SetOpacity(1.0f);
					Character->SummaryWidget->Img_MainEvidenceImage2->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 2){
					Character->SummaryWidget->Img_MainEvidenceImage3->SetOpacity(1.0f);
					Character->SummaryWidget->Img_MainEvidenceImage3->SetBrushFromTexture(SavedTexture);
				}
				break;
			case 3:
				if (PlayerID == 0){
					Character->SummaryWidget->Img_SpecialThingImage1->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SpecialThingImage1->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 1){
					Character->SummaryWidget->Img_SpecialThingImage2->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SpecialThingImage2->SetBrushFromTexture(SavedTexture);
				}
				else if (PlayerID == 2){
					Character->SummaryWidget->Img_SpecialThingImage3->SetOpacity(1.0f);
					Character->SummaryWidget->Img_SpecialThingImage3->SetBrushFromTexture(SavedTexture);
				}
				break;
			default:
				break;
			}
		}
	}
}

void ATP_ThirdPersonCharacter::ServerSetSummaryMulti_Implementation(int32 Category, UTexture2D* SavedTexture,
                                                                    int32 PlayerID){
	MulticastSetSummaryMulti(Category, SavedTexture, PlayerID);
	SetSummaryMulti(Category, SavedTexture, PlayerID);
}

void ATP_ThirdPersonCharacter::MulticastSetSummaryMulti_Implementation(int32 Category, UTexture2D* SavedTexture,
	int32 PlayerID){
	SetSummaryMulti(Category, SavedTexture, PlayerID);
}

void ATP_ThirdPersonCharacter::OnRep_PlayerState(){
	Super::OnRep_PlayerState();

	if (ps)
	{
		int32 PlayerIndex = ps->GetPlayerId();
		ServerSetCharacterMaterial(PlayerIndex);
	}
}

void ATP_ThirdPersonCharacter::SetCharacterMaterial(int32 PlayerID){
	if(gi->CustomizingDataArray.IsValidIndex(PlayerID)){
		const FCustomizingData& myData = gi->CustomizingDataArray[PlayerID];
		if(CoatMesh && HatMesh && MaterialArray.IsValidIndex(myData.CoatIdx) && MaterialArray.IsValidIndex(myData.HatIdx)){
			CoatMesh->SetMaterial(0, MaterialArray[myData.CoatIdx]);
			for (int32 i = 0; i < 4; i++){
				HatMesh->SetMaterial(i, MaterialArray[myData.HatIdx]);
			}
		}
	}
}

void ATP_ThirdPersonCharacter::ServerSetCharacterMaterial_Implementation(int32 PlayerID){
	MulticastSetCharacterMaterial(PlayerID);
}

void ATP_ThirdPersonCharacter::MulticastSetCharacterMaterial_Implementation(int32 PlayerID){
	SetCharacterMaterial(PlayerID);
}

void ATP_ThirdPersonCharacter::PlayInventorySound()
{
	{
		USoundWave* InventorySound = LoadObject<USoundWave>(nullptr, TEXT("/Game/KHH/Sound/Interaction_sound/Fast_book_paging.Fast_book_paging"));
		// UE_LOG(LogTemp, Warning, FString::Printf(TEXT("%s"), *InventorySound->GetPathName()));

		if ( InventorySound )
		{
			UGameplayStatics::PlaySound2D(GetWorld(), InventorySound);
		}
	}
}

void ATP_ThirdPersonCharacter::PlayEvidenceSound()
{
	if ( EvidenceSound )
	{
		UGameplayStatics::PlaySound2D(GetWorld(), EvidenceSound);
	}
}

void ATP_ThirdPersonCharacter::PlayPaperSound(){
	if ( PaperSound )
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PaperSound);
	}
}

void ATP_ThirdPersonCharacter::PlayMapSound()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if ( CurrentLevelName == "Main" && MainSound )
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MainSound);
	}
	else if ( CurrentLevelName == "Case" && CaseSound )
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CaseSound);
	}
} 
