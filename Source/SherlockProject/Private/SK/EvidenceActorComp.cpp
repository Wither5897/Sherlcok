// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/EvidenceActorComp.h"
#include "Kismet/KismetStringLibrary.h"
#include "EvidenceActor.h"
#include "Jin/AJH_WorldActor.h"

// Sets default values for this component's properties
UEvidenceActorComp::UEvidenceActorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEvidenceActorComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	me = Cast<AEvidenceActor>(GetOwner());
	worldActor = Cast<AAJH_WorldActor>(GetOwner());
}


// Called every frame
void UEvidenceActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UEvidenceActorComp::GetTagNum()
{

	FString tag = me->Tags[1].ToString();
	FString num = UKismetStringLibrary::GetSubstring(tag, 0, 2);

	return UKismetStringLibrary::Conv_StringToInt(num);
}

int32 UEvidenceActorComp::GetWorldActorTagNum()
{

	FString tag = worldActor->Tags[1].ToString();
	FString num = UKismetStringLibrary::GetSubstring(tag, 0, 2);

	return UKismetStringLibrary::Conv_StringToInt(num);
}

