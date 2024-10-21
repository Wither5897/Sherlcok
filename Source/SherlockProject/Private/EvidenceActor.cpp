// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AEvidenceActor::AEvidenceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    // 다양한 증거들도 동일하게 적용할 수 있도록 수정해야함.
    if ( Cube.Succeeded() )
    {
        StaticMesh->SetStaticMesh(Cube.Object);
    }
    StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

}

void AEvidenceActor::HighlightActor()
{
    StaticMesh->SetRenderCustomDepth(true);
    StaticMesh->SetCustomDepthStencilValue(2);
}

void AEvidenceActor::UnHighlightActor()
{
    if ( StaticMesh == nullptr ) return;
    StaticMesh->SetRenderCustomDepth(false);
}

// Called when the game starts or when spawned
void AEvidenceActor::BeginPlay()
{
	Super::BeginPlay();
    PlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AEvidenceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //PerformLineTrace();
}

//void AEvidenceActor::PerformLineTrace()
//{
//    if ( !PlayerController ) return;
//
//    FVector CameraLocation;
//    FRotator CameraRotation;
//    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
//
//    FVector Start = CameraLocation;
//    FVector End = Start + ( CameraRotation.Vector() * TraceDistance );
//
//    FHitResult HitResult;
//
//    bool bHit = GetWorld()->LineTraceSingleByChannel(
//        HitResult,
//        Start,
//        End,
//        ECC_Visibility
//    );
//
//    if ( bHit && HitResult.GetActor() )
//    {
//        if ( HitResult.GetActor() == this )
//        {
//            HighlightActor();
//        }
//        else
//        {
//            UnHighlightActor();
//        }
//        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
//    }
//    else
//    {
//        UnHighlightActor();
//    }
//}

