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
#include "SK/SaveLevelUI.h"

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
	
	pc = Cast<APlayerController>(GetController());
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

	SaveLevelWidget = Cast<USaveLevelUI>(CreateWidget(GetWorld(), SaveLevelWidgetFactory));
	if(SaveLevelWidget){
		SaveLevelWidget->AddToViewport();
	}

	EditorActor = Cast<AAJH_EditorActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorActor::StaticClass()));
	//WorldActor = Cast<AAJH_WorldActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_WorldActor::StaticClass()));
	IA_changeNum = 1;
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
		OnMyLocationGizmoMovement();
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
		input->BindAction(IA_LeftClick, ETriggerEvent::Completed, this, &AAJH_EditorCharacter::OnMyIA_EndLeftClick);
		input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_RightClick);
		input->BindAction(IA_RightClick, ETriggerEvent::Completed, this, &AAJH_EditorCharacter::OnMyIA_EndRightClick);
		input->BindAction(IA_LineTraceLeftClick, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_StartLineTraceLeftClick);
		input->BindAction(IA_LineTraceLeftClick, ETriggerEvent::Completed, this, &AAJH_EditorCharacter::OnMyIA_EndLineTraceLeftClick);
		input->BindAction(IA_changeLocation, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_changeLocation);
		input->BindAction(IA_changeRotation, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_changeRotation);
		input->BindAction(IA_changeScale, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_changeScale);
	}

}

void AAJH_EditorCharacter::OnMyIA_LookMouse(const FInputActionValue& value)
{
	MouseValue = value.Get<FVector2D>();

	// Gizmo 회전 처리
	if ( IA_changeNum == 2 && CurrentWorldActor && CurrentWorldActor->bIsAxisRotation )
	{
		bIsGizmoRotationActive = true;
		bIsGizmoScaleActive = false;
		OnMyHandleGizmoRotation();
	}
	else if ( IA_changeNum == 3 && CurrentWorldActor && CurrentWorldActor->bIsAxisScale )
	{
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = true;
		OnMyHandleGizmoScale();
	}
	else
	{
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = false;
		// Gizmo 회전 모드가 아닐 때 카메라 회전 처리
		AddControllerYawInput(MouseValue.X);
		AddControllerPitchInput(-MouseValue.Y);

		// 마우스 커서 상태 관리
		if ( pc )
		{
			pc->SetShowMouseCursor(false);
			pc->SetInputMode(FInputModeGameOnly());
		}
	}

}

void AAJH_EditorCharacter::OnMyIA_EditorMove(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();
	direction.X = v.X;
	direction.Y = v.Y;
}

void AAJH_EditorCharacter::OnMyIA_LeftClick()
{
	// Gizmo 상호작용 구분 및 마우스 커서 상태 설정
	if ( CurrentWorldActor )
	{
		// Rotation Gizmo일 때만 마우스 커서를 숨기기
		if ( IA_changeNum == 2 && CurrentWorldActor->bIsAxisRotation )
		{
			if ( pc )
			{
				pc->SetShowMouseCursor(false);
				pc->SetInputMode(FInputModeGameOnly());
			}
		}
		// Location Gizmo일 때 마우스 커서를 유지
		else if ( IA_changeNum == 1 && CurrentWorldActor->bIsAxisLocation )
		{
			if ( pc )
			{
				pc->SetShowMouseCursor(true);
				pc->SetInputMode(FInputModeGameAndUI());
			}
		}
	}
	else
	{
		// 허공을 클릭했을 때 마우스 커서를 숨기기
		if ( pc )
		{
			pc->SetShowMouseCursor(false);
			pc->SetInputMode(FInputModeGameOnly());
		}
	}

	// 기존의 액터 스폰 로직 유지
	if ( bIsActorSpawn && EditorActor != nullptr )
	{
		GetWorld()->SpawnActor<AAJH_WorldActor>(WorldActorFactory, EditorActor->GetActorTransform());
		EditorActor->bIsSpawn = false;
		EditorActor->Destroy();
		bIsEditorActor = false;
		bIsActorSpawn = false;
	}

}

void AAJH_EditorCharacter::OnMyIA_EndLeftClick()
{
	// 마우스 클릭을 놓았을 때 마우스 커서를 다시 표시합니다.
	if ( pc )
	{
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeGameAndUI());
	}

	// Gizmo 상호작용 상태 초기화
	if ( CurrentWorldActor )
	{
		CurrentWorldActor->bIsAxisLocation = false;
		CurrentWorldActor->bIsAxisRotation = false;
		CurrentWorldActor->bIsAxisScale = false;
	}

	GetCharacterMovement()->MaxFlySpeed = 1800;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Mouse Click Released"));
}

void AAJH_EditorCharacter::OnMyIA_RightClick()
{
	if (pc)
	{
		pc->bShowMouseCursor = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Right Click: Mouse Cursor Hidden"));
	}
}

void AAJH_EditorCharacter::OnMyIA_EndRightClick()
{
	if (pc)
	{
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
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
			if( IA_changeNum == 1 ) initialWorldLocation = worldLocation;
			if( IA_changeNum == 2 ) initialWorldRotation = worldRotation;
			if( IA_changeNum == 3 ) initialWorldScale = worldScale;
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

		// 초기 위치 및 회전값 저장
		actorInitialLocation = CurrentWorldActor->GetActorLocation();
		actorInitialRotation = CurrentWorldActor->GetActorRotation();
		actorInitialScale = CurrentWorldActor->GetActorScale3D();
		

		// Gizmo 상호작용 처리
		OnMyGizmoInteraction();

		if ( IA_changeNum == 1 )
		{
			CurrentWorldActor->LocationVisibility();
			LocationGizmoForSetCollision();
		}
		else if ( IA_changeNum == 2 )
		{
			CurrentWorldActor->RotationVisivility();
			RotationGizmoForSetCollision();
		}
		else if ( IA_changeNum == 3 )
		{
			CurrentWorldActor->ScaleVisivility();
			ScaleGizmoForSetCollision();
		}
	}
	else
	{
		// 허공을 클릭했거나 WorldActor가 아닌 액터를 클릭한 경우
		if ( CurrentWorldActor )
		{
			CurrentWorldActor->GizmoVisibility();
			CurrentWorldActor = nullptr;
		}
	}

	// 이전 WorldActor의 축 가시성을 초기화
	if ( LastInteractedWorldActor )
	{
		LastInteractedWorldActor->GizmoVisibility(); // 모든 축을 비활성화
		LastInteractedWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		LastInteractedWorldActor = nullptr; // 초기화
	}

	// 마지막으로 상호작용한 WorldActor 업데이트
	LastInteractedWorldActor = CurrentWorldActor;

	if ( CurrentWorldActor )
	{
		CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		if ( CurrentWorldActor->bIsAxisLocation )
		{
			CurrentWorldActor->LocationVisibility();
		}
		else if ( CurrentWorldActor->bIsAxisRotation )
		{
			CurrentWorldActor->RotationVisivility();
		}
	}
}

void AAJH_EditorCharacter::OnMyIA_EndLineTraceLeftClick()
{
	if ( outHit.GetComponent() != nullptr && CurrentWorldActor != nullptr )
	{
		CurrentWorldActor->bIsAxisLocation = false;
		CurrentWorldActor->bIsAxisRotation = false;
		CurrentWorldActor->bIsAxisScale = false;
		// Gizmo 회전이 끝난 후 마우스 커서를 다시 표시하고 UI 모드로 전환
		if ( pc )
		{
			bIsGizmoRotationActive = false;
			bIsGizmoScaleActive = false;
			pc->bShowMouseCursor = true;
			pc->SetInputMode(FInputModeGameAndUI());
		}
		GetCharacterMovement()->MaxFlySpeed = 1800;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("4444"), CurrentWorldActor->bIsAxisLocation);
	}
}

void AAJH_EditorCharacter::OnMyIA_changeLocation()
{
	IA_changeNum = 1;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 1")); // IA_changeNum 확인
	if ( CurrentWorldActor )
	{
		CurrentWorldActor->LocationVisibility();
		CurrentWorldActor->bIsVisibleLocation = true;
		CurrentWorldActor->bIsVisibleRotation = false;
		CurrentWorldActor->bIsAxisScale = false;
	}
}

void AAJH_EditorCharacter::OnMyIA_changeRotation()
{
	IA_changeNum = 2;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 2")); // IA_changeNum 확인
	if ( CurrentWorldActor )
	{
		CurrentWorldActor->RotationVisivility();
		CurrentWorldActor->bIsVisibleLocation = false;
		CurrentWorldActor->bIsVisibleRotation = true;
		CurrentWorldActor->bIsAxisScale = false;
	}
}

void AAJH_EditorCharacter::OnMyIA_changeScale()
{
	IA_changeNum = 3;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 3")); // IA_changeNum 확인
	if ( CurrentWorldActor )
	{
		CurrentWorldActor->ScaleVisivility();
		CurrentWorldActor->bIsVisibleLocation = false;
		CurrentWorldActor->bIsVisibleRotation = false;
		CurrentWorldActor->bIsAxisScale = true;
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

void AAJH_EditorCharacter::OnMyHandleGizmoRotation()
{
	if ( !pc || !outHit.GetComponent() )
	{
		return; // 안전한 포인터 체크
	}

	if ( bIsGizmoRotationActive )
	{
		pc->SetShowMouseCursor(false); // 회전 모드에서 마우스 커서 숨기기
		pc->SetInputMode(FInputModeGameOnly());
	}

	// 마우스 이동 값을 사용하여 회전값 계산
	float MouseX, MouseY;
	pc->GetInputMouseDelta(MouseX, MouseY); // 마우스 델타 값 가져오기

	deltaRotation = FRotator::ZeroRotator;

	// 선택된 축에 따라 회전값 수정
	if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Rot")) )
	{
		deltaRotation.Pitch += MouseY * 5.0f; // 회전 속도 조절
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along X Rot"));
	}
	if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Rot")) )
	{
		deltaRotation.Roll += -MouseY * 5.0f;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along Y Rot"));
	}
	if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Rot")) )
	{
		deltaRotation.Yaw += MouseX * 5.0f;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along Z Rot"));
	}

	// 회전값 적용
	CurrentWorldActor->AddActorLocalRotation(deltaRotation);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Rotation: ") + CurrentWorldActor->GetActorRotation().ToString());
}

void AAJH_EditorCharacter::OnMyHandleGizmoScale()
{
	if ( !pc || !outHit.GetComponent() )
	{
		return; // 안전한 포인터 체크
	}

	if ( bIsGizmoRotationActive )
	{
		pc->SetShowMouseCursor(false); // 회전 모드에서 마우스 커서 숨기기
		pc->SetInputMode(FInputModeGameOnly());
	}

	// 마우스 이동 값을 사용하여 Scale 값 계산
	float MouseX, MouseY;
	pc->GetInputMouseDelta(MouseX, MouseY); // 마우스 델타 값 가져오기

	float baseScaleFactor = 0.01f; // 기본 Scale 변화 속도
	float maxScaleFactor = 0.1f;   // 최대 Scale 변화 속도
	float scaleFactor = baseScaleFactor;

	// 마우스 입력이 임계값을 초과하면 ScaleFactor를 증가
	if ( FMath::Abs(MouseX) > 10.0f || FMath::Abs(MouseY) > 10.0f )
	{
		scaleFactor = maxScaleFactor;
	}

	newScale = actorInitialScale;

	// 선택된 축에 따라 Scale 값 수정
	if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Scale")) )
	{
		newScale.X = FMath::Clamp(newScale.X + MouseX * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scalting along X Scale"));
	}
	else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Scale")) )
	{
		newScale.Y = FMath::Clamp(newScale.Y + MouseX * scaleFactor, 0.1f, 10.0f);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scaling along Y Scale"));
	}
	else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Scale")) )
	{
		newScale.Z = FMath::Clamp(newScale.Z + MouseY * scaleFactor, 0.1f, 10.0f);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scaling along Z Scale"));
	}

	// Scale 값 적용
	CurrentWorldActor->SetActorScale3D(newScale);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Scale: ") + CurrentWorldActor->GetActorScale().ToString());
}

void AAJH_EditorCharacter::LocationGizmoForSetCollision()
{
	// Location
	CurrentWorldActor->X_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Y_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Z_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->XYZ_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	// Rotation
	CurrentWorldActor->X_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	// Scale
	CurrentWorldActor->X_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void AAJH_EditorCharacter::RotationGizmoForSetCollision()
{
	// Location
	CurrentWorldActor->X_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->XYZ_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	// Rotation
	CurrentWorldActor->X_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Y_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Z_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	// Scale
	CurrentWorldActor->X_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void AAJH_EditorCharacter::ScaleGizmoForSetCollision()
{
	// Location
	CurrentWorldActor->X_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->XYZ_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	// Rotation
	CurrentWorldActor->X_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Y_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CurrentWorldActor->Z_Rot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	// Scale
	CurrentWorldActor->X_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Y_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CurrentWorldActor->Z_Scale->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAJH_EditorCharacter::OnMyLocationGizmoMovement()
{
	float currentMouseX, currentMouseY;
	if ( pc && pc->GetMousePosition(currentMouseX, currentMouseY) )
	{
		if ( pc->DeprojectScreenPositionToWorld(currentMouseX, currentMouseY, worldLocation, worldDirection) )
		{
			if ( IA_changeNum == 1 )
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
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("outHit.GetComponent() is nullptr"));
		}
	}
}

void AAJH_EditorCharacter::OnMyGizmoInteraction()
{
	UPrimitiveComponent* HitComponent = outHit.GetComponent();

	if ( !CurrentWorldActor || !HitComponent ) return; // 안전한 NULL 체크

	// 디버그 메시지로 충돌한 컴포넌트 확인
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
		FString::Printf(TEXT("Hit Component: %s"), *HitComponent->GetName()));
	// 현재 상태 및 IA_changeNum 값 디버깅
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
		FString::Printf(TEXT("IA_changeNum: %d"), IA_changeNum));

	// 충돌된 컴포넌트의 태그를 확인하여 상태 설정
	if ( HitComponent->ComponentHasTag(TEXT("X_Axis")) || HitComponent->ComponentHasTag(TEXT("Y_Axis")) || HitComponent->ComponentHasTag(TEXT("Z_Axis")) ||	HitComponent->ComponentHasTag(TEXT("XYZ_Axis")) )
	{
		if ( IA_changeNum == 1 )
		{
			SetGizmoState(EGizmoState::Location); // Location 상태 설정
		}
	}
	else if ( HitComponent->ComponentHasTag(TEXT("X_Rot")) || HitComponent->ComponentHasTag(TEXT("Y_Rot")) || HitComponent->ComponentHasTag(TEXT("Z_Rot")) )
	{
		if ( IA_changeNum == 2 )
		{
			SetGizmoState(EGizmoState::Rotation); // Rotation 상태 설정
		}
	}
	// 스케일 Gizmo를 추가할 경우
	else if ( HitComponent->ComponentHasTag(TEXT("X_Scale")) ||	 HitComponent->ComponentHasTag(TEXT("Y_Scale")) || HitComponent->ComponentHasTag(TEXT("Z_Scale")) )
	{
		if (IA_changeNum == 3)
		{
			SetGizmoState(EGizmoState::Scale); // Scale 상태 설정
		}
	}

}

void AAJH_EditorCharacter::SetGizmoState(EGizmoState GizmoState)
{
	if ( !CurrentWorldActor || !pc ) return;

	// 현재 상태를 저장
	CurrentGizmoState = GizmoState;

	// 모든 상태 초기화
	CurrentWorldActor->bIsAxisLocation = false;
	CurrentWorldActor->bIsAxisRotation = false;
	CurrentWorldActor->GizmoVisibility();

	// 충돌 초기화: 모든 Gizmo 충돌을 제거
	CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	// 디버그 메시지: 상태 초기화 확인
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Gizmo State and Collisions Reset"));

	switch ( GizmoState )
	{
	case EGizmoState::Location:
		CurrentWorldActor->bIsAxisLocation = true;
		pc->bShowMouseCursor = true; // 마우스 커서 표시
		CurrentWorldActor->LocationVisibility();
		LocationGizmoForSetCollision();
		break;
	case EGizmoState::Rotation:
		CurrentWorldActor->bIsAxisRotation = true;
		pc->bShowMouseCursor = false; // 마우스 커서 숨기기
		CurrentWorldActor->RotationVisivility();
		RotationGizmoForSetCollision();
		break;
	case EGizmoState::Scale:
		CurrentWorldActor->bIsAxisScale = true;
		pc->bShowMouseCursor = false; // 마우스 커서 숨기기
		CurrentWorldActor->ScaleVisivility();
		ScaleGizmoForSetCollision();
		break;
	default:
		break;
	}

	// 디버그 메시지로 상태 전환 확인
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow,
		FString::Printf(TEXT("Setting Gizmo State: %d"), static_cast< int32 >( GizmoState )));

	// 이동 속도를 0으로 설정하여 캐릭터 이동 방지
	GetCharacterMovement()->MaxFlySpeed = 0;
}

