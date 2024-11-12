// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_GizmoUI.h"
#include "Components/WidgetSwitcher.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableText.h"

void UAJH_GizmoUI::NativeConstruct()
{
	player = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Switcher_GizmoUI->SetActiveWidgetIndex(0);
	
	OnMyEdit_Location();
	GetEdit_Location();


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

