// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_UserNameTagWidget.h"
#include "Components/TextBlock.h"


void UAJH_UserNameTagWidget::SetUserName(FString value)
{
	Txt_UserName->SetText(FText::FromString(value));
}
