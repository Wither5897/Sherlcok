// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SK/InventoryWidget.h"
#include "Components/Button.h"
#include "SK/DescriptionWidget.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	Inven = Cast<UInventoryWidget>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	if ( Inven ) {
		DescriptionUI = Inven->DescriptionUI;
	}

	if ( GetMyNumber() >= 1 ) {
		Evidence->SetColorAndOpacity(ItemColor[( GetMyNumber() - 1 ) % 8]);
	}
	Player1Light->SetVisibility(ESlateVisibility::Hidden);
	Player2Light->SetVisibility(ESlateVisibility::Hidden);
	Player3Light->SetVisibility(ESlateVisibility::Hidden);

	ItemButton->OnClicked.AddDynamic(this, &UItemWidget::ItemButtonClicked);
}

int32 UItemWidget::GetMyNumber()
{
	int32 value = UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 2, 2));
	return value;
}

void UItemWidget::WhenFindItem()
{
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);
	Player1Light->SetVisibility(ESlateVisibility::Visible);
}

void UItemWidget::ItemButtonClicked()
{
	WhenFindItem();
	if ( Inven->DescriptionUI ) {
		Inven->DescriptionUI->WhenItemClicked(GetMyNumber());
	}
	int32 MyNumber = GetMyNumber();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("My Number: %d"), MyNumber));
}
