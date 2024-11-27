// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/LightWidget.h"

#include "Components/Button.h"
#include "Components/DirectionalLightComponent.h"
#include "Jin/AJH_DirectionalLight.h"
#include "Jin/AJH_Sun.h"
#include "Kismet/GameplayStatics.h"

void ULightWidget::NativeConstruct(){
	Super::NativeConstruct();

	directionalLightActor = Cast<AAJH_DirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_DirectionalLight::StaticClass()));
	Btn_morning->OnClicked.AddDynamic(this, &ULightWidget::OnMyBtn_morning);
	Btn_lunch->OnClicked.AddDynamic(this, &ULightWidget::OnMyBtn_lunch);
	Btn_Dinner->OnClicked.AddDynamic(this, &ULightWidget::OnMyBtn_Dinner);

	SunActor = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
}

void ULightWidget::OnMyBtn_morning(){
	SKSunHeight = 0.33f;
	SunActor->RefreshMateiral(SKSunHeight);
	directionalLightActor->directionalLightComp->SetIntensity(10.0f);
	sunColor = FLinearColor(0.705882, 0.792157, 1.0f);
	directionalLightActor->directionalLightComp->SetLightColor(sunColor);
	directionalLightActor->SetActorRotation(FRotator(-55.0f, 0.0f, 0.0f));
}

void ULightWidget::OnMyBtn_lunch(){
	SKSunHeight = 1.f;
	SunActor->RefreshMateiral(SKSunHeight);
	directionalLightActor->directionalLightComp->SetIntensity(10.0f);
	sunColor = FLinearColor(1.0f, 1.0f, 1.0f);
	directionalLightActor->directionalLightComp->SetLightColor(sunColor);
	directionalLightActor->SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void ULightWidget::OnMyBtn_Dinner(){
	SKSunHeight = -1.f;
	SunActor->RefreshMateiral(SKSunHeight);
	directionalLightActor->directionalLightComp->SetIntensity(0.4f);
	sunColor = FLinearColor(0.403922, 0.545098, 1.0f);
	directionalLightActor->directionalLightComp->SetLightColor(sunColor);
	directionalLightActor->SetActorRotation(FRotator(270.0f, 180.0f, 180.0f));
}
