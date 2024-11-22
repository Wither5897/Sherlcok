// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditerToolGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_WorldActor.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Jin/AJH_EditorPlayerController.h"

AAJH_EditerToolGameMode::AAJH_EditerToolGameMode()
{
    // 기본 PlayerController와 DefaultPawn 설정
    PlayerControllerClass = AAJH_EditorPlayerController::StaticClass();
    DefaultPawnClass = AAJH_EditorCharacter::StaticClass();
}

//void AAJH_EditerToolGameMode::WorldActorLocation(const FVector& NewLocation)
//{
//    AAJH_WorldActor* WorldActor = Cast<AAJH_WorldActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_WorldActor::StaticClass()));
//    if ( WorldActor )
//    {
//        WorldActor->SetActorLocation(NewLocation);
//        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Actor Location Updated"));
//    }
//}

void AAJH_EditerToolGameMode::BeginPlay()
{
    
}
