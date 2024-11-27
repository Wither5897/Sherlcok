// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_LightWidget.h"
#include "Components/Button.h"
#include "Jin/AJH_DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Jin/AJH_Sun.h"

void UAJH_LightWidget::NativeConstruct()
{
	// player = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	directionalLightActor = Cast<AAJH_DirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_DirectionalLight::StaticClass()));
	// MorningSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MorningSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MiddaySun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MidnightSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	
	Btn_morning->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_morning);
	Btn_lunch->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_lunch);
	Btn_Dinner->OnClicked.AddDynamic(this, &UAJH_LightWidget::OnMyBtn_Dinner);
	
}

void UAJH_LightWidget::OnMyBtn_morning()
{
	//directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-7, 0, 0));
	MorningSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MiddaySun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MidnightSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	if ( !bIsMorningSun )
	{
		GetWorld()->DestroyActor(MorningSun);
		bIsMorningSun = true;
		directionalLightActor->directionalLightComp->SetIntensity(10.0f);
		sunColor = FLinearColor(0.705882, 0.792157, 1.0f);
		directionalLightActor->directionalLightComp->SetLightColor(sunColor);
		directionalLightActor->SetActorRotation(FRotator(-55.0f, 0.0f, 0.0f));
		MorningSun = GetWorld()->SpawnActor<AAJH_Sun>(MorningSunFactory, directionalLightActor->GetActorTransform());
		MorningSun->height_Sun = 0.33f;
		SunActor = MorningSun;
	}
	else
	{
		return;
	}

	if ( bIsMiddaySun )
	{
		bIsMiddaySun = false;
		GetWorld()->DestroyActor(MiddaySun);
	}

	if ( bIsMidnightSun )
	{	
		bIsMidnightSun = false;
		GetWorld()->DestroyActor(MidnightSun);
	}
}

void UAJH_LightWidget::OnMyBtn_lunch()
{
	//directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-46, 0, 0));
	MorningSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MiddaySun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MidnightSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	if ( !bIsMiddaySun )
	{
		
		GetWorld()->DestroyActor(MiddaySun);
		bIsMiddaySun = true;
		directionalLightActor->directionalLightComp->SetIntensity(10.0f);
		sunColor = FLinearColor(1.0f, 1.0f, 1.0f);
		directionalLightActor->directionalLightComp->SetLightColor(sunColor);
		directionalLightActor->SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
		MiddaySun = GetWorld()->SpawnActor<AAJH_Sun>(MiddaySunFactory, directionalLightActor->GetActorTransform());
		MiddaySun->height_Sun = 1.0f;
		SunActor = MiddaySun;
	}
	else
	{
		return;
	}

	if ( bIsMorningSun )
	{
		bIsMorningSun = false;
		GetWorld()->DestroyActor(MorningSun);
	}

	if ( bIsMidnightSun )
	{
		bIsMidnightSun = false;
		GetWorld()->DestroyActor(MidnightSun);
	}
}

void UAJH_LightWidget::OnMyBtn_Dinner()
{
	//directionalLightActor->directionalLightComp->SetRelativeRotation(FRotator(-3.5, 180, 180));
	MorningSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MiddaySun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	MidnightSun = Cast<AAJH_Sun>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_Sun::StaticClass()));
	if ( !bIsMidnightSun )
	{
		GetWorld()->DestroyActor(MidnightSun);
		bIsMidnightSun = true;
		directionalLightActor->directionalLightComp->SetIntensity(0.4f);
		sunColor = FLinearColor(0.403922, 0.545098, 1.0f);
		directionalLightActor->directionalLightComp->SetLightColor(sunColor);
		directionalLightActor->SetActorRotation(FRotator(270.0f, 180.0f, 180.0f));
		MidnightSun = GetWorld()->SpawnActor<AAJH_Sun>(MidnightSunFactory, directionalLightActor->GetActorTransform());
		MidnightSun->height_Sun = -1.0f;
		SunActor = MidnightSun;
	}
	else
	{
		return;
	}

	if ( bIsMorningSun )
	{
		bIsMorningSun = false;
		GetWorld()->DestroyActor(MorningSun);
	}

	if ( bIsMiddaySun )
	{
		bIsMiddaySun = false;
		GetWorld()->DestroyActor(MiddaySun);
	}
}
