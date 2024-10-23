// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceActor.h"
#include "Components/StaticMeshComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"


// Sets default values
AEvidenceActor::AEvidenceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if ( Cube.Succeeded() )
    {
        StaticMesh->SetStaticMesh(Cube.Object);
    }
    StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

// Called when the game starts or when spawned
void AEvidenceActor::BeginPlay()
{
	Super::BeginPlay();
    //PlayerController = GetWorld()->GetFirstPlayerController();
}

