// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_WorldActor.h"

// Sets default values
AAJH_WorldActor::AAJH_WorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
	X_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Axis"));
	X_Axis->SetupAttachment(MeshComp);
	X_Axis->ComponentTags.Add(TEXT("X_Axis"));
	Y_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Axis"));
	Y_Axis->SetupAttachment(MeshComp);
	Y_Axis->ComponentTags.Add(TEXT("Y_Axis"));
	Z_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Axis"));
	Z_Axis->SetupAttachment(MeshComp);
	Z_Axis->ComponentTags.Add(TEXT("Z_Axis"));

}

// Called when the game starts or when spawned
void AAJH_WorldActor::BeginPlay()
{
	Super::BeginPlay();

	bIsAxisLocation = false;
	ResetVisibility();

}

// Called every frame
void AAJH_WorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_WorldActor::ResetVisibility()
{
	X_Axis->SetVisibility(false);
	Y_Axis->SetVisibility(false);
	Z_Axis->SetVisibility(false);
}

