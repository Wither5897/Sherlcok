﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_LightWidget.h"
#include "Components/Button.h"
#include "Jin/AJH_DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorCharacter.h"

void UAJH_LightWidget::NativeConstruct()
{
	directionalLightActor = Cast<AAJH_DirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_DirectionalLight::StaticClass()));
	
	Btn_morning->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_morning);
	Btn_lunch->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_lunch);
	Btn_Dinner->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_Dinner);
}

void UAJH_LightWidget::OnMyBtn_morning()
{
	directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-7, 0, 0));
}

void UAJH_LightWidget::OnMyBtn_lunch()
{
	directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-75, 0, 0));
}

void UAJH_LightWidget::OnMyBtn_Dinner()
{
	directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-3.5, 180, 180));
}
