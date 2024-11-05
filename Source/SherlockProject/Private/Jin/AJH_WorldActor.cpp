// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_WorldActor.h"

// Sets default values
AAJH_WorldActor::AAJH_WorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAJH_WorldActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAJH_WorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

