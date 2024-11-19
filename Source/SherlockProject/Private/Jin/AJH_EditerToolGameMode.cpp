// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditerToolGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_WorldActor.h"

void AAJH_EditerToolGameMode::WorldActorLocation(const FVector& NewLocation)
{
    AAJH_WorldActor* WorldActor = Cast<AAJH_WorldActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_WorldActor::StaticClass()));
    if ( WorldActor )
    {
        WorldActor->SetActorLocation(NewLocation);
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Actor Location Updated"));
    }
}
