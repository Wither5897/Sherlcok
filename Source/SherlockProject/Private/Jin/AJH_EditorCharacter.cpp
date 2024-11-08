// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Jin/AJH_EditorToolWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorActor.h"
#include "Jin/AJH_WorldActor.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAJH_EditorCharacter::AAJH_EditorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(RootComponent);

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
	//WorldActor = Cast<AAJH_WorldActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_WorldActor::StaticClass()));
}

// Called every frame
void AAJH_EditorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform t = FTransform(GetControlRotation());
	direction = t.TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;

	if ( CurrentWorldActor && CurrentWorldActor->bIsAxisLocation )
	{
		float currentMouseX, currentMouseY;
		if ( pc && pc->GetMousePosition(currentMouseX, currentMouseY) )
		{
			if ( pc->DeprojectScreenPositionToWorld(currentMouseX, currentMouseY, worldLocation, worldDirection) )
			{
				deltaLocation = worldLocation - initialWorldLocation;
				if ( deltaLocation.IsNearlyZero(0.01f) ) return; // 이동 값이 작으면 무시

				float scaleFactor = 23.0f; // 이동 속도 조절
				deltaLocation *= scaleFactor;

				newLocation = actorInitialLocation;
				if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Axis")) )
				{
					newLocation.X += deltaLocation.X;
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along X Axis"));
				}
				if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Axis")) )
				{
					newLocation.Y += deltaLocation.Y;
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along Y Axis"));
				}
				if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Axis")) )
				{
					newLocation.Z += deltaLocation.Z;
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along Z Axis"));
				}
				if ( outHit.GetComponent()->ComponentHasTag(TEXT("XYZ_Axis")) )
				{
					newLocation += deltaLocation;
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along XYZ Axis"));
				}

				// 좌표 갱신
				CurrentWorldActor->SetActorLocation(newLocation);
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Location: ") + newLocation.ToString());
			}
		}

	}
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
		input->BindAction(IA_LineTraceLeftClick, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_StartLineTraceLeftClick);
		input->BindAction(IA_LineTraceLeftClick, ETriggerEvent::Completed, this, &AAJH_EditorCharacter::OnMyIA_EndLineTraceLeftClick);
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
		bIsActorSpawn = false;
	}
	else
	{
		return;
	}
}

void AAJH_EditorCharacter::OnMyIA_RightClick()
{
	
}

void AAJH_EditorCharacter::OnMyIA_StartLineTraceLeftClick()
{
	if ( bIsEditorActor )
	{
		return;
	}

	// LineTrace 수행
	OnMyLineTrace();
	float currentMouseX, currentMouseY;
	if ( pc && pc->GetMousePosition(currentMouseX, currentMouseY) )
	{
		if ( pc->DeprojectScreenPositionToWorld(currentMouseX, currentMouseY, worldLocation, worldDirection) )
		{
			initialWorldLocation = worldLocation;
		}
	}

	// 디버그 메시지: 라인 트레이스 결과 출력
	if ( outHit.GetActor() != nullptr )
	{
		FString hitActorName = outHit.GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Hit Actor: ") + hitActorName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No Actor Hit"));
	}

	// 현재 LineTrace로 맞은 WorldActor 설정
	if ( outHit.GetActor() != nullptr && outHit.GetActor()->ActorHasTag(TEXT("Actor")) )
	{
		CurrentWorldActor = Cast<AAJH_WorldActor>(outHit.GetActor());
		actorInitialLocation = CurrentWorldActor->GetActorLocation();
		actorInitialRotation = CurrentWorldActor->GetActorRotation();
	}
	else
	{
		// 허공을 클릭했거나 WorldActor가 아닌 액터를 클릭한 경우
		CurrentWorldActor = nullptr;
	}

	// 이전 WorldActor의 축 가시성을 초기화
	if ( LastInteractedWorldActor && ( CurrentWorldActor == nullptr || LastInteractedWorldActor != CurrentWorldActor ) )
	{
		LastInteractedWorldActor->LocationVisibility();
		LastInteractedWorldActor->RotationVisivility();
		LastInteractedWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		LastInteractedWorldActor = nullptr; // 초기화
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0000"));
	}

	// 현재 WorldActor의 축 가시성을 활성화 (CurrentWorldActor가 nullptr 이 아닐 때만)
	/*if ( CurrentWorldActor && CurrentWorldActor->bIsAxisLocation )
	{
		CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		CurrentWorldActor->X_Axis->SetVisibility(true);
		CurrentWorldActor->Y_Axis->SetVisibility(true);
		CurrentWorldActor->Z_Axis->SetVisibility(true);
		CurrentWorldActor->XYZ_Axis->SetVisibility(true);
	}
	else if ( CurrentWorldActor && CurrentWorldActor->bIsAxisRotation )
	{
		CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		CurrentWorldActor->X_Rot->SetVisibility(true);
		CurrentWorldActor->Y_Rot->SetVisibility(true);
		CurrentWorldActor->Z_Rot->SetVisibility(true);
	}*/
	if ( CurrentWorldActor )
	{
		CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		if ( CurrentWorldActor->bIsAxisLocation )
		{
			CurrentWorldActor->LocationVisibility();
		}
		/*if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Axis")) ||
			outHit.GetComponent()->ComponentHasTag(TEXT("Y_Axis")) ||
			outHit.GetComponent()->ComponentHasTag(TEXT("Z_Axis")) ||
			outHit.GetComponent()->ComponentHasTag(TEXT("XYZ_Axis")) )
		{
			CurrentWorldActor->LocationVisibility();
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Axis Location Visibility Activated"));
		}*/
		else if ( CurrentWorldActor->bIsAxisRotation )
		{
			CurrentWorldActor->RotationVisivility();
		}
		/*else if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Rot")) ||
				 outHit.GetComponent()->ComponentHasTag(TEXT("Y_Rot")) ||
				 outHit.GetComponent()->ComponentHasTag(TEXT("Z_Rot")) )
		{
			CurrentWorldActor->RotationVisivility();
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Axis Rotation Visibility Activated"));
		}*/
	}

	// 축 가시성 및 상태 설정 (CurrentWorldActor가 nullptr이 아닐 때만)
	if ( CurrentWorldActor && outHit.GetComponent() )
	{
		if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Axis")) )
		{
			CurrentWorldActor->bIsAxisLocation = true;
			GetCharacterMovement()->MaxFlySpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("X_Axis"));
		}
		else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Axis")) )
		{
			CurrentWorldActor->bIsAxisLocation = true;
			GetCharacterMovement()->MaxFlySpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Y_Axis"));
		}
		else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Axis")) )
		{
			CurrentWorldActor->bIsAxisLocation = true;
			GetCharacterMovement()->MaxFlySpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Z_Axis"));
		}
		else if ( outHit.GetComponent()->ComponentHasTag(TEXT("XYZ_Axis")) )
		{
			CurrentWorldActor->bIsAxisLocation = true;
			GetCharacterMovement()->MaxFlySpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("XYZ_Axis"));
		}
	}

	// 마지막으로 상호작용한 WorldActor 업데이트
	LastInteractedWorldActor = CurrentWorldActor;

}

void AAJH_EditorCharacter::OnMyIA_EndLineTraceLeftClick()
{
	if ( outHit.GetComponent() != nullptr && CurrentWorldActor != nullptr )
	{
		CurrentWorldActor->bIsAxisLocation = false;
		CurrentWorldActor->bIsAxisRotation = false;
		GetCharacterMovement()->MaxFlySpeed = 1000;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("4444"), CurrentWorldActor->bIsAxisLocation);
	}
}

void AAJH_EditorCharacter::OnMouseUpdateActorLocation()
{
	// 마우스 움직임 가져오기
	FVector2D currentMousePosition;
	if ( pc->GetMousePosition(currentMousePosition.X, currentMousePosition.Y) )
	{
		FVector2D mouseDelta = currentMousePosition - initialMousePosition;
		initialMousePosition = currentMousePosition; // 마우스 위치를 갱신

		// 마우스 움직임 값을 X축 위치에 반영 (Y 및 Z는 0으로 고정)
		deltaLocation = FVector(mouseDelta.X * 1.0f, 0.0f, 0.0f); // 0.1f는 스케일링 팩터
		newLocation = CurrentWorldActor->GetActorLocation() + deltaLocation;
		CurrentWorldActor->SetActorLocation(newLocation);

		// 디버그 메시지 출력
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Location: ") + newLocation.ToString());
	}
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

void AAJH_EditorCharacter::OnMyLineTrace()
{
	FVector WorldLocation, WorldDirection, Start, End;
	if ( pc->DeprojectMousePositionToWorld(WorldLocation, WorldDirection) )
	{
		Start = WorldLocation;
		End = WorldLocation + ( WorldDirection * 5000.0f );

		FCollisionQueryParams param;
		param.AddIgnoredActor(this);
		bool bHit = GetWorld()->LineTraceSingleByChannel(outHit, Start, End, ECC_Visibility, param);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 3);
		if ( bHit && outHit.GetActor() != nullptr )
		{
			FString objectName = outHit.GetActor()->GetName();
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Object Hit: ") + objectName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No Object Hit"));
		}
	}
}

