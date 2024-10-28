// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_SummaryWidget.h"
#include "Components/Button.h"
#include "SK/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"

void UAJH_SummaryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if ( Btn_Click )
	{
		Btn_Click->OnClicked.AddDynamic(this, &UAJH_SummaryWidget::OnMyBtn_Click);
	}

	// InventoryUI가 null인 경우 생성
	if ( !InventoryUI )
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if ( PC )
		{
			InventoryUI = CreateWidget<UInventoryWidget>(PC, UInventoryWidget::StaticClass());
			if ( !InventoryUI )
			{
				UE_LOG(LogTemp, Error, TEXT("InventoryUI 위젯을 생성할 수 없습니다."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController를 가져올 수 없습니다."));
		}
	}
}

void UAJH_SummaryWidget::OnMyBtn_Click()
{
	if ( InventoryUI && InventoryUI->SuspectImage )
	{
		Img_Inven = InventoryUI->SuspectImage;
		UE_LOG(LogTemp, Warning, TEXT("살려주세여"));
		UE_LOG(LogTemp, Warning, TEXT("Yes"), Img_Inven);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryUI 또는 SuspectImage가 null 상태입니다."));
	}
	
}
