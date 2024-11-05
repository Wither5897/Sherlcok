// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Components/BoxComponent.h"
#include "../Public/UW_ReportBoard.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ABoard::ABoard()
{
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMesh);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardMesh(TEXT("/Game/TJ/Asset_Main/board2/new_york_city_police_investigation_board.new_york_city_police_investigation_board"));
    if ( BoardMesh.Succeeded() )
    {
        StaticMesh->SetStaticMesh(BoardMesh.Object);
    }

	BoxArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxArea->SetupAttachment(RootComponent);

	BoxArea->SetRelativeLocation(FVector(1.0f, 2.0f, 70.0f));
	BoxArea->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	BoxArea->SetRelativeScale3D(FVector(1.5f, 3.25f, 2.0f));

	BoxArea->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));

    WidgetReportBoard = CreateDefaultSubobject<UWidgetComponent>(TEXT("ReportBoard"));
    WidgetReportBoard->SetupAttachment(RootComponent);
    
    WidgetReportBoard->SetRelativeLocation(FVector(-0.0f, 2.0f, 70.0f));
    WidgetReportBoard->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    WidgetReportBoard->SetRelativeScale3D(FVector(0.13f, 0.13f, 0.13f));

    static ConstructorHelpers::FClassFinder<UUW_ReportBoard> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/Board/SKWBP_ReportBoard2.SKWBP_ReportBoard2_C'"));
    if ( WidgetClass.Succeeded() )
    {
        WidgetReportBoard->SetWidgetClass(WidgetClass.Class);
    }
    WidgetReportBoard->SetDrawSize(FVector2D(1550, 900));
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoard::SetVisibleBoard() {
    
}


