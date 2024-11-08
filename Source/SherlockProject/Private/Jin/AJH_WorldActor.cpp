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
	XYZ_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XYZ_Axis"));
	XYZ_Axis->SetupAttachment(MeshComp);
	XYZ_Axis->ComponentTags.Add(TEXT("XYZ_Axis"));
	X_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Rot"));
	X_Rot->SetupAttachment(MeshComp);
	X_Rot->ComponentTags.Add(TEXT("X_Rot"));
	Y_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Rot"));
	Y_Rot->SetupAttachment(MeshComp);
	Y_Rot->ComponentTags.Add(TEXT("Y_Rot"));
	Z_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Rot"));
	Z_Rot->SetupAttachment(MeshComp);
	Z_Rot->ComponentTags.Add(TEXT("Z_Rot"));

}

// Called when the game starts or when spawned
void AAJH_WorldActor::BeginPlay()
{
	Super::BeginPlay();

	GizmoVisibility();
	bIsVisibleLocation = false;
	bIsVisibleRotation = false;

}

// Called every frame
void AAJH_WorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_WorldActor::GizmoVisibility()
{
	X_Axis->SetVisibility(false);
	Y_Axis->SetVisibility(false);
	Z_Axis->SetVisibility(false);
	XYZ_Axis->SetVisibility(false);
	X_Rot->SetVisibility(false);
	Y_Rot->SetVisibility(false);
	Z_Rot->SetVisibility(false);
}

void AAJH_WorldActor::LocationVisibility()
{
	//bIsAxisLocation = true;
	//bIsAxisRotation = false;

	// Location 축 활성화
	X_Axis->SetVisibility(true);
	Y_Axis->SetVisibility(true);
	Z_Axis->SetVisibility(true);
	XYZ_Axis->SetVisibility(true);
	

	// Rotation 축 비활성화
	X_Rot->SetVisibility(false);
	Y_Rot->SetVisibility(false);
	Z_Rot->SetVisibility(false);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("LocationVisibility called"));
}

void AAJH_WorldActor::RotationVisivility()
{
	//bIsAxisLocation = false;
	//bIsAxisRotation = true;

	// Rotation 축 활성화
	X_Rot->SetVisibility(true);
	Y_Rot->SetVisibility(true);
	Z_Rot->SetVisibility(true);

	// Location 축 비활성화
	X_Axis->SetVisibility(false);
	Y_Axis->SetVisibility(false);
	Z_Axis->SetVisibility(false);
	XYZ_Axis->SetVisibility(false);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("RotationVisivility called"));

}

