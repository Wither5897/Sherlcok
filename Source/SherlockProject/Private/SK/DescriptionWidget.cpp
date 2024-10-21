// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/DescriptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDescriptionWidget::NativeConstruct()
{	
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UDescriptionWidget::BackButtonClicked);

	SetVisibility(ESlateVisibility::Hidden);
	
}

void UDescriptionWidget::WhenItemClicked(int32 value)
{
	SetVisibility(ESlateVisibility::Visible);
	FText text;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("value: %d"), value));
	switch (value)
	{
	case 1:
		text = FText::FromString(FString::Printf(TEXT("텍스트의 길이가 어느정도까지 가능한지 테스트 하는 용도로 작성하고 있는 중입니다. 근데 이거 옵션을 킬 수 있었던거 같은데 어디에 있더라 이거 빨리 찾아보고 적용해야겠는데, 슬슬 적을 말이 없어지고 있다. 벌써 10시가 다 되어가는데 시간 버그인가 아니면 내가 버그인가 나는 벌레인가 벌레가맞는거 같기도 하고")));
		SetDescriptionText(text);
		break;
	case 2:
		text = FText::FromString(FString::Printf(TEXT("나는 집에 가고 싶다")));
		SetDescriptionText(text);
		break;
	case 3:
		text = FText::FromString(FString::Printf(TEXT("배고프다")));
		SetDescriptionText(text);
		break;
	case 4: 
		text = FText::FromString(FString::Printf(TEXT("오늘은 뭘 먹을까")));
		SetDescriptionText(text);
		break;
	case 5:
		text = FText::FromString(FString::Printf(TEXT("잠이온다")));
		SetDescriptionText(text);
		break;
	case 6:
		text = FText::FromString(FString::Printf(TEXT("...")));
		SetDescriptionText(text);
		break;
	case 7:
		text = FText::FromString(FString::Printf(TEXT("테스트 7")));
		SetDescriptionText(text);
		break;
	case 8:
		text = FText::FromString(FString::Printf(TEXT("테스트 8")));
		SetDescriptionText(text);
		break;
	default:
		text = FText::FromString(FString::Printf(TEXT("테스트 9 ~ 16")));
		SetDescriptionText(text);
		break;
	}
	return;
}

void UDescriptionWidget::SetDescriptionText(FText NewText)
{
	ItemDescription->SetText(NewText);
	/*FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UDescriptionWidget::SetUIVisibility, 1.5f);*/
}

void UDescriptionWidget::SetUIVisibility()
{
	if (IsVisible()) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UDescriptionWidget::BackButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
