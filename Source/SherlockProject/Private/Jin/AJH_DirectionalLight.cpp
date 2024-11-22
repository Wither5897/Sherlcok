// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

// Sets default values
AAJH_DirectionalLight::AAJH_DirectionalLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	directionalLightComp = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLightComp"));
	SetRootComponent(directionalLightComp);
	directionalLightComp->SetRelativeRotation(FRotator(-46, 0,0));

}

// Called when the game starts or when spawned
void AAJH_DirectionalLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAJH_DirectionalLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

