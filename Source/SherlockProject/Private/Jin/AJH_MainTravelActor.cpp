// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_MainTravelActor.h"
#include "Components/BoxComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AAJH_MainTravelActor::AAJH_MainTravelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mainTravelBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MainTravelBoxComp"));
	SetRootComponent(mainTravelBoxComp);

}

// Called when the game starts or when spawned
void AAJH_MainTravelActor::BeginPlay()
{
	Super::BeginPlay();
	
	mainTravelBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AAJH_MainTravelActor::OnMyMainTravelBoxBeginOverlap);
	

}

// Called every frame
void AAJH_MainTravelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_MainTravelActor::OnMyMainTravelBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AAJH_MainTravelActor::OnMyMainTravelBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

