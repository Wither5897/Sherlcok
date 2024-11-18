// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_GizmoUI.h"
#include "Components/WidgetSwitcher.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableText.h"
#include "Jin/AJH_EditerToolGameMode.h"
#include "Jin/AJH_WorldActor.h"

void UAJH_GizmoUI::NativeConstruct()
{
	player = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Switcher_GizmoUI->SetActiveWidgetIndex(0);
	
	OnMyEdit_Location();
	OnMyEdit_Rotation();
	OnMyEdit_Scale();

	if ( Edit_Location_X )
	{
		Edit_Location_X->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyLocationTextCommitted);
	}
	if ( Edit_Location_Y )
	{
		Edit_Location_Y->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyLocationTextCommitted);
	}
	if ( Edit_Location_Z )
	{
		Edit_Location_Z->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyLocationTextCommitted);
	}

	if ( Edit_Rotation_Roll )
	{
		Edit_Rotation_Roll->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyRotationTextCommitted);
	}
	if ( Edit_Rotation_Pitch )
	{
		Edit_Rotation_Pitch->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyRotationTextCommitted);
	}
	if ( Edit_Rotation_Yaw )
	{
		Edit_Rotation_Yaw->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyRotationTextCommitted);
	}

	if ( Edit_Scale_X )
	{
		Edit_Scale_X->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyScaleTextCommitted);
	}
	if ( Edit_Scale_Y )
	{
		Edit_Scale_Y->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyScaleTextCommitted);
	}
	if ( Edit_Scale_Z )
	{
		Edit_Scale_Z->OnTextCommitted.AddDynamic(this, &UAJH_GizmoUI::OnMyScaleTextCommitted);
	}
}

void UAJH_GizmoUI::OnMyEdit_Location()
{
	if ( player )
	{
		Location_X = FString::FromInt(player->newLocation.X);
		// UEditableText에 값 설정
		Edit_Location_X->SetText(FText::FromString(Location_X));
		Location_Y = FString::FromInt(player->newLocation.Y);
		Edit_Location_Y->SetText(FText::FromString(Location_Y));
		Location_Z = FString::FromInt(player->newLocation.Z);
		Edit_Location_Z->SetText(FText::FromString(Location_Z));
	}
}

void UAJH_GizmoUI::GetEdit_Location()
{
	Location_X = FString::FromInt(actorLocation.X);
	Edit_Location_X->SetText(FText::FromString(Location_X));
	Location_Y = FString::FromInt(actorLocation.Y);
	Edit_Location_Y->SetText(FText::FromString(Location_Y)); 
	Location_Z = FString::FromInt(actorLocation.Z);
	Edit_Location_Z->SetText(FText::FromString(Location_Z));
}

void UAJH_GizmoUI::OnMyLocationTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter && player )
	{
		// 입력된 텍스트를 FVector로 변환
		float X = FCString::Atof(*Edit_Location_X->GetText().ToString());
		float Y = FCString::Atof(*Edit_Location_Y->GetText().ToString());
		float Z = FCString::Atof(*Edit_Location_Z->GetText().ToString());

		FVector NewLocation(X, Y, Z);

		// AAJH_EditorCharacter의 CurrentWorldActor에 위치 설정
		if ( player->CurrentWorldActor )
		{
			player->CurrentWorldActor->SetActorLocation(NewLocation);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Actor Location Updated"));
		}
	}
}

void UAJH_GizmoUI::OnMyEdit_Rotation()
{
	if ( player )
	{
		Rotation_Roll = FString::FromInt(player->deltaRotation.Roll);
		Edit_Rotation_Roll->SetText(FText::FromString(Rotation_Roll));
		Rotation_Pitch = FString::FromInt(player->deltaRotation.Pitch);
		Edit_Rotation_Pitch->SetText(FText::FromString(Rotation_Pitch));
		Rotation_Yaw = FString::FromInt(player->deltaRotation.Yaw);
		Edit_Rotation_Yaw->SetText(FText::FromString(Rotation_Yaw));
	}
}

void UAJH_GizmoUI::GetEdit_Rotation(FRotator NewRotation)
{
	Rotation_Roll = FString::FromInt(NewRotation.Roll);
	Edit_Rotation_Roll->SetText(FText::FromString(Rotation_Roll));
	Rotation_Pitch = FString::FromInt(NewRotation.Pitch);
	Edit_Rotation_Pitch->SetText(FText::FromString(Rotation_Pitch));
	Rotation_Yaw = FString::FromInt(NewRotation.Yaw);
	Edit_Rotation_Yaw->SetText(FText::FromString(Rotation_Yaw));
}

void UAJH_GizmoUI::OnMyRotationTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter && player )
	{
		// 입력된 텍스트를 FVector로 변환
		float Roll = FCString::Atof(*Edit_Rotation_Roll->GetText().ToString());
		float Pitch = FCString::Atof(*Edit_Rotation_Pitch->GetText().ToString());
		float Yaw = FCString::Atof(*Edit_Rotation_Yaw->GetText().ToString());

		FRotator NewRotation(Roll, Pitch, Yaw);

		// AAJH_EditorCharacter의 CurrentWorldActor에 위치 설정
		if ( player->CurrentWorldActor )
		{
			player->CurrentWorldActor->SetActorRotation(NewRotation);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Actor Rotation Updated"));
		}
	}
}

void UAJH_GizmoUI::OnMyEdit_Scale()
{
	if ( player )
	{
		Scale_X = FString::Printf(TEXT("%.2f"), player->newScale.X);
		Edit_Scale_X->SetText(FText::FromString(Scale_X));
		Scale_Y = FString::Printf(TEXT("%.2f"), player->newScale.Y);
		Edit_Scale_Y->SetText(FText::FromString(Scale_Y));
		Scale_Z = FString::Printf(TEXT("%.2f"), player->newScale.Z);
		Edit_Scale_Z->SetText(FText::FromString(Scale_Z));
	}
}

void UAJH_GizmoUI::GetEdit_Scale(FVector NewScale)
{
	Scale_X = FString::Printf(TEXT("%.2f"), NewScale.X);
	Edit_Scale_X->SetText(FText::FromString(Scale_X));
	Scale_Y = FString::Printf(TEXT("%.2f"), NewScale.Y);
	Edit_Scale_Y->SetText(FText::FromString(Scale_Y));
	Scale_Z = FString::Printf(TEXT("%.2f"), NewScale.Z);
	Edit_Scale_Z->SetText(FText::FromString(Scale_Z));
}

void UAJH_GizmoUI::OnMyScaleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter && player )
	{
		// 입력된 텍스트를 FVector로 변환
		float X = FCString::Atof(*Edit_Scale_X->GetText().ToString());
		float Y = FCString::Atof(*Edit_Scale_Y->GetText().ToString());
		float Z = FCString::Atof(*Edit_Scale_Z->GetText().ToString());

		FVector NewScale(X, Y, Z);

		// AAJH_EditorCharacter의 CurrentWorldActor에 위치 설정
		if ( player->CurrentWorldActor )
		{
			player->CurrentWorldActor->SetActorScale3D(NewScale);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Actor Scale Updated"));
		}
	}
}

