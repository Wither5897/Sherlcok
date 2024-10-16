// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), );
	GetMyNumber() - 1;
}

int32 UItemWidget::GetMyNumber()
{
	return UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 1, 1));
}

void UItemWidget::WhenFindItem()
{
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);
}
