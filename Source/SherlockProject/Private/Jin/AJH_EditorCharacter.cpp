﻿// Fill out your copyright notice in the Description page of Project Settings.


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
#include "AJH_GizmoUI.h"
#include "Jin/AJH_EscapeWidget.h"
#include "Jin/AJH_ExPlainBtnWidget.h"
#include "UW_EditorExplain.h"
#include "Components/Button.h"
#include "Jin/AJH_LightWidget.h"
#include "Jin/AJH_EditorPlayerController.h"
#include "SK/LightWidget.h"

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
	
	pc = Cast<AAJH_EditorPlayerController>(GetController());
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

	EscapeWidget = Cast<UAJH_EscapeWidget>(CreateWidget(GetWorld(), EscapeWidgetFactory));
	if ( EscapeWidget )
	{
		EscapeWidget->AddToViewport();
		EscapeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	SaveLevelWidget = Cast<USaveLevelUI>(CreateWidget(GetWorld(), SaveLevelWidgetFactory));
	if(SaveLevelWidget){
		SaveLevelWidget->AddToViewport();
	}

	GizmoUI = Cast<UAJH_GizmoUI>(CreateWidget(GetWorld(), GizmoUIFactory));
	if ( GizmoUI )
	{
		GizmoUI->AddToViewport();
	}

	LightWidget = Cast<ULightWidget>(CreateWidget(GetWorld(), LightWidgetFactory));
	if ( LightWidget )
	{
		LightWidget->AddToViewport();
	}
	
	
	
	/*ExPlainBtnWidget = Cast<UAJH_ExPlainBtnWidget>(CreateWidget(GetWorld(), ExPlainBtnFactory));
	if ( ExPlainBtnWidget )
	{
		ExPlainBtnWidget->AddToViewport();
		ExPlainBtnWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	EditorExplain = Cast<UUW_EditorExplain>(CreateWidget(GetWorld(), EditorExplainFactory));
	if ( EditorExplain )
	{
		EditorExplain->AddToViewport();
		EditorExplain->SetVisibility(ESlateVisibility::Collapsed);
	}*/

	EditorActor = Cast<AAJH_EditorActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorActor::StaticClass()));
	EditorSpawn = Cast<AAJH_EditorActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorActor::StaticClass()));
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

	if ( CurrentWorldActor && IA_changeNum == 1 && CurrentWorldActor->bIsAxisLocation )
	{
		OnMyLocationGizmoMovement();
	}

	// UpdateGizmoScale();
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
		input->BindAction(IA_Escape, ETriggerEvent::Started, this, &AAJH_EditorCharacter::OnMyIA_Escape);
	}

}

void AAJH_EditorCharacter::OnMyIA_LookMouse(const FInputActionValue& value)
{
	MouseValue = value.Get<FVector2D>();

	// Gizmo 회전 처리
	if ( IA_changeNum == 2 && CurrentWorldActor && CurrentWorldActor->bIsAxisRotation )
	{
		bIsGizmoLocationActive = false;
		bIsGizmoRotationActive = true;
		bIsGizmoScaleActive = false;
		OnMyHandleGizmoRotation();
	}
	else if ( IA_changeNum == 3 && CurrentWorldActor && CurrentWorldActor->bIsAxisScale )
	{
		bIsGizmoLocationActive = false;
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = true;
		OnMyHandleGizmoScale();
	}
	else
	{
		bIsGizmoLocationActive = true;
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
		if ( FactoryChange )
		{
			UGameplayStatics::PlaySound2D(GetWorld(), HeavystompSound);
			GetWorld()->SpawnActor<AAJH_WorldActor>(FactoryChange, EditorActor->GetActorTransform());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FactoryChange is nullptr! Cannot spawn actor."));
		}
		//GetWorld()->SpawnActor<AAJH_WorldActor>(WorldActorFactory, EditorActor->GetActorTransform());
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

	if ( outHit.GetActor() != nullptr)
	{
		bHasInteractedWithGizmo = true; // Gizmo와 상호작용이 감지되었을 때 true로 설정
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Gizmo interaction detected!"));
	}
	else
	{
		bHasInteractedWithGizmo = false; // Gizmo와 상호작용하지 않은 경우 false
	}

	// 디버그 메시지: 라인 트레이스 결과 출력
	if ( outHit.GetActor() != nullptr )
	{
		FString hitActorName = outHit.GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Hit Actor: ") + hitActorName);
		// CurrentWorldActor 설정 및 디버깅
		CurrentWorldActor = Cast<AAJH_WorldActor>(outHit.GetActor());
		if ( CurrentWorldActor )
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("CurrentWorldActor Set Successfully"));
			// Gizmo 상호작용 호출
			OnMyGizmoInteraction();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("CurrentWorldActor is nullptr!"));
		}
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

		GizmoUI->actorLocation = actorInitialLocation;
		GizmoUI->GetEdit_Location();
		GizmoUI->actorRotation = actorInitialRotation;
		GizmoUI->GetEdit_Rotation(actorInitialRotation);
		GizmoUI->actorScale = actorInitialScale;
		GizmoUI->GetEdit_Scale(actorInitialScale);

		CurrentWorldActor->ExPlainBtnWidget->SetVisibility(ESlateVisibility::Visible);
		if ( CurrentWorldActor->bIsInterative )
		{
			CurrentWorldActor->ExPlainBtnWidget->OnEnableBtn_ExPlain(true);
		}
		else
		{
			CurrentWorldActor->ExPlainBtnWidget->OnEnableBtn_ExPlain(false);
		}

		if ( IA_changeNum == 1 )
		{
			bIsGizmoLocationActive = true;
			bIsGizmoRotationActive = false;
			bIsGizmoScaleActive = false;
			CurrentWorldActor->LocationVisibility();
			LocationGizmoForSetCollision();
			GetCharacterMovement()->MaxFlySpeed = 0;
		}
		else if ( IA_changeNum == 2 )
		{
			bIsGizmoLocationActive = false;
			bIsGizmoRotationActive = true;
			bIsGizmoScaleActive = false;
			CurrentWorldActor->RotationVisivility();
			RotationGizmoForSetCollision();
			GetCharacterMovement()->MaxFlySpeed = 0;
		}
		else if ( IA_changeNum == 3 )
		{
			bIsGizmoLocationActive = false;
			bIsGizmoRotationActive = false;
			bIsGizmoScaleActive = true;
			CurrentWorldActor->ScaleVisivility();
			ScaleGizmoForSetCollision();
			GetCharacterMovement()->MaxFlySpeed = 0;
		}
	}
	else
	{
		// 허공을 클릭했거나 WorldActor가 아닌 액터를 클릭한 경우
		if ( CurrentWorldActor )
		{
			CurrentWorldActor->GizmoVisibility();
			CurrentWorldActor->bIsAxisLocation = false;
			CurrentWorldActor->bIsAxisRotation = false;
			CurrentWorldActor->bIsAxisScale = false;
			CurrentWorldActor->ExPlainBtnWidget->SetVisibility(ESlateVisibility::Collapsed);
			// CurrentWorldActor = nullptr;
		}
	}

	// 이전 WorldActor의 축 가시성을 초기화
	if ( LastInteractedWorldActor )
	{
		LastInteractedWorldActor->GizmoVisibility(); // 모든 축을 비활성화
		LastInteractedWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		LastInteractedWorldActor->ExPlainBtnWidget->SetVisibility(ESlateVisibility::Collapsed);
		// LastInteractedWorldActor = nullptr; // 초기화
	}

	if ( CurrentWorldActor )
	{
		CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		if ( CurrentWorldActor->bIsAxisLocation )
		{
			CurrentWorldActor->bIsAxisLocation = true;
			CurrentWorldActor->bIsAxisRotation = false;
			CurrentWorldActor->bIsAxisScale = false;
			CurrentWorldActor->LocationVisibility();
		}
		else if ( CurrentWorldActor->bIsAxisRotation )
		{
			CurrentWorldActor->bIsAxisLocation = false;
			CurrentWorldActor->bIsAxisRotation = true;
			CurrentWorldActor->bIsAxisScale = false;
			CurrentWorldActor->RotationVisivility();
		}
		else if ( CurrentWorldActor->bIsAxisScale )
		{
			CurrentWorldActor->bIsAxisLocation = false;
			CurrentWorldActor->bIsAxisRotation = false;
			CurrentWorldActor->bIsAxisScale = true;
			CurrentWorldActor->ScaleVisivility();
		}
	}

	if ( outHit.GetActor() != nullptr && outHit.GetActor()->ActorHasTag(TEXT("InteractObj")) )
	{
		CurrentWorldActor->ExPlainBtnWidget->OnEnableBtn_ExPlain(true);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT(str: ") + CurrentWorldActor->ExplainText);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentWorldActor->ExplainText);
	}

	// 마지막으로 상호작용한 WorldActor 업데이트
	LastInteractedWorldActor = CurrentWorldActor;
}

void AAJH_EditorCharacter::OnMyIA_EndLineTraceLeftClick()
{
	if ( outHit.GetComponent() != nullptr && CurrentWorldActor != nullptr )
	{
		// Gizmo 회전이 끝난 후 마우스 커서를 다시 표시하고 UI 모드로 전환
		if ( pc )
		{
			pc->bShowMouseCursor = true;
			pc->SetInputMode(FInputModeGameAndUI());
		}

		bIsGizmoLocationActive = false;
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = false;

		if ( CurrentWorldActor )
		{
			CurrentWorldActor->bIsAxisLocation = false;
			CurrentWorldActor->bIsAxisRotation = false;
			CurrentWorldActor->bIsAxisScale = false;
		}

		GetCharacterMovement()->MaxFlySpeed = 1800;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("4444"), CurrentWorldActor->bIsAxisLocation);
	}
}

void AAJH_EditorCharacter::OnMyIA_changeLocation()
{
	// Gizmo가 이미 활성화된 상태라면 함수 실행을 중단
	if ( IA_changeNum == 1 && CurrentWorldActor && CurrentWorldActor->bIsAxisLocation )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo is already in Location mode."));
		return; // 이미 활성화된 상태이므로 중단
	}

	if ( bIsGizmoLocationStart ) return;

	IA_changeNum = 1;
	bIsGizmoRotationStart = false;
	bIsGizmoScaleStart = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 1")); // IA_changeNum 확인


	SetGizmoState(EGizmoState::Location);
}

void AAJH_EditorCharacter::OnMyIA_changeRotation()
{
	// Gizmo가 이미 활성화된 상태라면 함수 실행을 중단
	if ( IA_changeNum == 2 && CurrentWorldActor && CurrentWorldActor->bIsAxisRotation )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo is already in Location mode."));
		return; // 이미 활성화된 상태이므로 중단
	}

	if( bIsGizmoRotationStart ) return;

	IA_changeNum = 2;
	bIsGizmoLocationStart = false;
	bIsGizmoScaleStart = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 2")); // IA_changeNum 확인

	SetGizmoState(EGizmoState::Rotation);
}

void AAJH_EditorCharacter::OnMyIA_changeScale()
{
	// Gizmo가 이미 활성화된 상태라면 함수 실행을 중단
	if ( IA_changeNum == 3 && CurrentWorldActor && CurrentWorldActor->bIsAxisScale )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo is already in Location mode."));
		return; // 이미 활성화된 상태이므로 중단
	}
	
	if( bIsGizmoScaleStart ) return;

	IA_changeNum = 3;
	bIsGizmoLocationStart = false;
	bIsGizmoRotationStart = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_changeNum is 3")); // IA_changeNum 확인

	SetGizmoState(EGizmoState::Scale);
}

void AAJH_EditorCharacter::OnMyIA_Escape()
{
	EscapeWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAJH_EditorCharacter::OnMyEditorActorSpawn(bool bIsSpawn)
{
	// 새로운 액터 스폰
	if ( bIsSpawn)
	{
		pc->GetHitResultUnderCursorByChannel(query, true, outHit);
		FTransform transform(outHit.Location);

		EditorActor = GetWorld()->SpawnActor<AAJH_EditorActor>(EditorChange, transform);
		if ( EditorActor )
		{
			EditorActor->bIsSpawn = true;
			bIsActorSpawn = true;
			bIsEditorActor = true;
		}
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

	if ( bIsGizmoRotationStart )
	{

		// 마우스 이동 값을 사용하여 회전값 계산
		float MouseX, MouseY;
		pc->GetInputMouseDelta(MouseX, MouseY); // 마우스 델타 값 가져오기

		// 입력값 무시 임계값 설정
		const float Threshold = 0.1f; // 임계값: 필요에 따라 조정 가능

		// 임계값보다 작은 입력값은 무시
		if ( FMath::Abs(MouseX) < Threshold )
		{
			MouseX = 0.0f; // MouseX 값 무시
		}
		if ( FMath::Abs(MouseY) < Threshold )
		{
			MouseY = 0.0f; // MouseY 값 무시
		}

		deltaRotation = FRotator::ZeroRotator;

		// 선택된 축에 따라 회전값 수정
		if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Rot")) )
		{
			if(MouseX)
				deltaRotation.Roll += MouseX * 5.0f; // 회전 속도 조절
			else if(MouseY)
				deltaRotation.Roll += MouseY * 5.0f; // 회전 속도 조절
			else if(MouseX && MouseY)
				deltaRotation.Roll += ((MouseX +MouseY) / 2) * 5.0f; // 회전 속도 조절

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along X Rot"));
		} 
		if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Rot")) )
		{
			if(MouseX)
				deltaRotation.Pitch += MouseX * 5.0f;
			else if(MouseY)
				deltaRotation.Pitch += MouseY * 5.0f;
			else if ( MouseX && MouseY )
				deltaRotation.Pitch += ( ( MouseX + MouseY ) / 2 ) * 5.0f; // 회전 속도 조절
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along Y Rot"));
		}
		if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Rot")) )
		{
			if ( MouseX )
				deltaRotation.Yaw += MouseX * 5.0f;
			else if ( MouseY )
				deltaRotation.Yaw += MouseY * 5.0f;
			else if ( MouseX && MouseY )
				deltaRotation.Yaw += ( ( MouseX + MouseY ) / 2 ) * 5.0f; // 회전 속도 조절
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Rotating along Z Rot"));
		}

		// 회전값 적용
		//CurrentWorldActor->AddActorLocalRotation(deltaRotation);
		CurrentWorldActor->MeshComp->AddLocalRotation(deltaRotation);
		//CurrentWorldActor->OnFixGizmoRotation();
		GizmoUI->GetEdit_Rotation(CurrentWorldActor->MeshComp->GetComponentRotation());
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Rotation: ") + CurrentWorldActor->GetActorRotation().ToString());
	}
	else
	{
		return;
	}
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

	if ( bIsGizmoScaleStart )
	{
		// 마우스 이동 값을 사용하여 Scale 값 계산
		float MouseX, MouseY;
		pc->GetInputMouseDelta(MouseX, MouseY); // 마우스 델타 값 가져오기

		float baseScaleFactor = 0.01f; // 기본 Scale 변화 속도
		float maxScaleFactor = 1.0f;   // 최대 Scale 변화 속도
		float scaleFactor = baseScaleFactor;

		// 이전 스케일 값을 가져와서 업데이트
		//FVector currentScale = CurrentWorldActor->GetActorScale3D();
		FVector currentScale = CurrentWorldActor->MeshComp->GetRelativeScale3D();
		newScale = currentScale; // 이전 스케일 값으로 설정
		
		// 입력값 무시 임계값 설정
		const float Threshold = 0.1f;

		// 임계값보다 작은 입력값은 무시
		if ( FMath::Abs(MouseX) < Threshold )
		{
			MouseX = 0.0f; // MouseX 값 무시
		}
		if ( FMath::Abs(MouseY) < Threshold )
		{
			MouseY = 0.0f; // MouseY 값 무시
		}

		// 선택된 축에 따라 Scale 값 수정
		if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Scale")) )
		{
			if(MouseX)
			newScale.X = FMath::Clamp(newScale.X + MouseX * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if(MouseY)
			newScale.X = FMath::Clamp(newScale.X + MouseY * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if(MouseX && MouseY)
			newScale.X = FMath::Clamp(newScale.X + ((MouseX + MouseY) / 2 ) * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scalting along X Scale"));
		}
		else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Scale")) )
		{
			if ( MouseX )
				newScale.Y = FMath::Clamp(newScale.Y + MouseX * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if ( MouseY )
				newScale.Y = FMath::Clamp(newScale.Y + MouseY * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if ( MouseX && MouseY )
				newScale.Y = FMath::Clamp(newScale.Y + ( ( MouseX + MouseY ) / 2 ) * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scaling along Y Scale"));
		}
		else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Scale")) )
		{
			if ( MouseX )
				newScale.Z = FMath::Clamp(newScale.Z + MouseX * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if ( MouseY )
				newScale.Z = FMath::Clamp(newScale.Z + MouseY * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			else if ( MouseX && MouseY )
				newScale.Z = FMath::Clamp(newScale.Z + ( ( MouseX + MouseY ) / 2 ) * scaleFactor, 0.1f, 10.0f); // 안전한 범위 내에서 변화
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Scaling along Z Scale"));
		}

		// Scale 값 적용
		//CurrentWorldActor->SetActorScale3D(newScale);
		//CurrentWorldActor->OnFixGizmoScale();
		CurrentWorldActor->MeshComp->SetRelativeScale3D(newScale);
		GizmoUI->GetEdit_Scale(CurrentWorldActor->MeshComp->GetRelativeScale3D());
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Scale: ") + CurrentWorldActor->GetActorScale().ToString());
	}
	else
	{
		return;
	}
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
	// CurrentWorldActor와 pc가 널인지 확인
	if ( !CurrentWorldActor || !pc )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("CurrentWorldActor or PlayerController is null!"));
		return; // 안전한 반환
	}

	// 추가 체크: outHit의 컴포넌트가 널이 아닌지 확인
	if ( !outHit.GetComponent() )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("outHit.GetComponent() is null!"));
		return;
	}

	// Gizmo와 실제로 상호작용했는지 확인
	if ( !bHasInteractedWithGizmo )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("No interaction with Gizmo detected."));
		return; // Gizmo와 상호작용하지 않았다면 함수 실행 중단
	}

	float currentMouseX, currentMouseY;
	if ( pc && pc->GetMousePosition(currentMouseX, currentMouseY) && bIsGizmoLocationStart )
	{
		if ( pc->DeprojectScreenPositionToWorld(currentMouseX, currentMouseY, worldLocation, worldDirection) )
		{
			if ( IA_changeNum == 1 )
			{
				 deltaLocation = worldLocation - initialWorldLocation;
				if ( deltaLocation.IsNearlyZero(0.01f) ) return; // 이동 값이 작으면 무시

				float scaleFactor = 23.0f; // 이동 속도 조절
				deltaLocation *= scaleFactor;

				// 이동 벡터를 액터의 로컬 좌표계로 변환
				//FVector localDeltaLocation = CurrentWorldActor->GetTransform().InverseTransformVectorNoScale(deltaLocation);

				newLocation = actorInitialLocation; // 초기 위치로 설정
				if ( outHit.GetComponent()->ComponentHasTag(TEXT("X_Axis")) )
				{
					newLocation += CurrentWorldActor->GetActorForwardVector() * deltaLocation.X; // X축만 이동
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along X Axis"));
				}
				else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Y_Axis")) )
				{
					newLocation += CurrentWorldActor->GetActorRightVector() * deltaLocation.Y; // Y축만 이동
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along Y Axis"));
				}
				else if ( outHit.GetComponent()->ComponentHasTag(TEXT("Z_Axis")) )
				{
					newLocation += CurrentWorldActor->GetActorUpVector() * deltaLocation.Z; // Z축만 이동
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along Z Axis"));
				}
				else if ( outHit.GetComponent()->ComponentHasTag(TEXT("XYZ_Axis")) )
				{
					newLocation += deltaLocation; // 모든 축 이동
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Moving along XYZ Axis"));
				}

				// 좌표 갱신
				CurrentWorldActor->SetActorLocation(newLocation);
				GizmoUI->OnMyEdit_Location();
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Updated Actor Location: ") + newLocation.ToString());
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("outHit.GetComponent() is nullptr"));
		}
	}
	else
	{
		return;
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
			bIsGizmoLocationStart = true;
			SetGizmoState(EGizmoState::Location); // Location 상태 설정
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo State: Location"));
		}
	}
	else if ( HitComponent->ComponentHasTag(TEXT("X_Rot")) || HitComponent->ComponentHasTag(TEXT("Y_Rot")) || HitComponent->ComponentHasTag(TEXT("Z_Rot")) )
	{
		if ( IA_changeNum == 2 )
		{
			bIsGizmoRotationStart = true;
			SetGizmoState(EGizmoState::Rotation); // Rotation 상태 설정

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo State: Rotation"));
		}
	}
	else if ( HitComponent->ComponentHasTag(TEXT("X_Scale")) ||	 HitComponent->ComponentHasTag(TEXT("Y_Scale")) || HitComponent->ComponentHasTag(TEXT("Z_Scale")) )
	{
		if (IA_changeNum == 3)
		{
			bIsGizmoScaleStart = true;
			SetGizmoState(EGizmoState::Scale); // Scale 상태 설정
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Gizmo State: Scale"));
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
	CurrentWorldActor->bIsAxisScale = false;
	CurrentWorldActor->GizmoVisibility();

	// Gizmo 상태 플래그 초기화
	bIsGizmoLocationActive = false;
	bIsGizmoRotationActive = false;
	bIsGizmoScaleActive = false;

	// 충돌 초기화: 모든 Gizmo 충돌을 제거
	CurrentWorldActor->MeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	// 디버그 메시지: 상태 초기화 확인
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Gizmo State and Collisions Reset"));

	switch ( GizmoState )
	{
	case EGizmoState::Location:
		CurrentWorldActor->bIsAxisLocation = true;
		bIsGizmoLocationActive = true;
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = false;
		pc->bShowMouseCursor = true; // 마우스 커서 표시
		CurrentWorldActor->LocationVisibility();
		LocationGizmoForSetCollision();
		break;
	case EGizmoState::Rotation:
		CurrentWorldActor->bIsAxisRotation = true;
		bIsGizmoLocationActive = false;
		bIsGizmoRotationActive = true;
		bIsGizmoScaleActive = false;
		//pc->bShowMouseCursor = false; // 마우스 커서 숨기기
		CurrentWorldActor->RotationVisivility();
		RotationGizmoForSetCollision();
		break;
	case EGizmoState::Scale:
		CurrentWorldActor->bIsAxisScale = true;
		bIsGizmoLocationActive = false;
		bIsGizmoRotationActive = false;
		bIsGizmoScaleActive = true;
		//pc->bShowMouseCursor = false; // 마우스 커서 숨기기
		CurrentWorldActor->ScaleVisivility();
		ScaleGizmoForSetCollision();
		break;
	default:
		break;
	}

	// 모든 포인터가 유효한지 체크
	if ( !CurrentWorldActor )
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("CurrentWorldActor is null after setting Gizmo state."));
		return;
	}

	// 디버그 메시지로 상태 전환 확인
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow,
		FString::Printf(TEXT("Setting Gizmo State: %d"), static_cast< int32 >( GizmoState )));

	// 이동 속도를 0으로 설정하여 캐릭터 이동 방지
	// GetCharacterMovement()->MaxFlySpeed = 0;
}

void AAJH_EditorCharacter::UpdateGizmoScale()
{
	if ( !CurrentWorldActor || !pc )
	{
		return; // Gizmo 또는 PlayerController가 없는 경우 반환
	}

	// Player의 위치와 Gizmo(현재 World Actor)의 위치를 가져옵니다.
	FVector PlayerLocation = GetActorLocation();
	FVector GizmoLocation = CurrentWorldActor->GetActorLocation();

	//// Gizmo의 RootComponent를 사용하여 World 좌표를 Local 좌표로 변환합니다.
	//FVector PlayerLocalLocation = CurrentWorldActor->GetRootComponent()->GetComponentTransform().InverseTransformPosition(PlayerLocation);

	// 거리 계산
	float Distance = FVector::Distance(PlayerLocation, GizmoLocation);
	// // 거리 계산 (이제 Local 좌표를 사용)
	//float Distance = FVector::Distance(PlayerLocalLocation, FVector::ZeroVector); // Gizmo의 Local 기준으로 거리

	// 거리 기반으로 스케일을 조정 (조정 가능한 상수값 사용)
	float ScaleFactor = FMath::Clamp(Distance / 1000.0f, 2.0f, 10.0f); // 최소 2.0, 최대 10.0

	// Gizmo의 각 축 컴포넌트에 개별적으로 스케일 설정
	CurrentWorldActor->X_Axis->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Y_Axis->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Z_Axis->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->XYZ_Axis->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->X_Rot->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Y_Rot->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Z_Rot->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->X_Scale->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Y_Scale->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
	CurrentWorldActor->Z_Scale->SetRelativeScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
}

