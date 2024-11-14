// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_WorldActor.h"

// Sets default values
AAJH_WorldActor::AAJH_WorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
	Tags.Add(TEXT("Actor"));
	X_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Axis"));
	X_Axis->SetupAttachment(MeshComp);
	X_Axis->ComponentTags.Add(TEXT("X_Axis"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempX_Axis.Succeeded() )
	{
		X_Axis->SetStaticMesh(tempX_Axis.Object);
		X_Axis->SetRelativeLocation(FVector(30.0f, 0.0f,0.0f));
		X_Axis->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		X_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	Y_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Axis"));
	Y_Axis->SetupAttachment(MeshComp);
	Y_Axis->ComponentTags.Add(TEXT("Y_Axis"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempY_Axis.Succeeded() )
	{
		Y_Axis->SetStaticMesh(tempY_Axis.Object);
		Y_Axis->SetRelativeLocation(FVector(0.0f, 30.0f, 0.0f));
		Y_Axis->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		Y_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	Z_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Axis"));
	Z_Axis->SetupAttachment(MeshComp);
	Z_Axis->ComponentTags.Add(TEXT("Z_Axis"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempZ_Axis.Succeeded() )
	{
		Z_Axis->SetStaticMesh(tempZ_Axis.Object);
		Z_Axis->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f)); 
		Z_Axis->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); 
		Z_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f)); 
	}
	XYZ_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XYZ_Axis"));
	XYZ_Axis->SetupAttachment(MeshComp);
	XYZ_Axis->ComponentTags.Add(TEXT("XYZ_Axis"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempXYZ_Axis(TEXT("'/Engine/VREditor/TransformGizmo/UniformScaleHandle.UniformScaleHandle'"));
	if ( tempXYZ_Axis.Succeeded() )
	{
		XYZ_Axis->SetStaticMesh(tempXYZ_Axis.Object);
		XYZ_Axis->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); 
		XYZ_Axis->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); 
		XYZ_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f)); 
	}
	X_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Rot"));
	X_Rot->SetupAttachment(MeshComp);
	X_Rot->ComponentTags.Add(TEXT("X_Rot"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempX_Rot.Succeeded() )
	{
		X_Rot->SetStaticMesh(tempX_Rot.Object);
		X_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		X_Rot->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		X_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	Y_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Rot"));
	Y_Rot->SetupAttachment(MeshComp);
	Y_Rot->ComponentTags.Add(TEXT("Y_Rot"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempY_Rot.Succeeded() )
	{
		Y_Rot->SetStaticMesh(tempY_Rot.Object);
		Y_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Y_Rot->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Y_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	Z_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Rot"));
	Z_Rot->SetupAttachment(MeshComp);
	Z_Rot->ComponentTags.Add(TEXT("Z_Rot"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempZ_Rot.Succeeded() )
	{
		Z_Rot->SetStaticMesh(tempZ_Rot.Object);
		Z_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Z_Rot->SetRelativeRotation(FRotator(-90.0f, 360.0f, 0.0f)); 
		Z_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	X_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Scale"));
	X_Scale->SetupAttachment(MeshComp);
	X_Scale->ComponentTags.Add(TEXT("X_Scale"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempX_Scale.Succeeded() )
	{
		X_Scale->SetStaticMesh(tempX_Scale.Object);
		X_Scale->SetRelativeLocation(FVector(65.0f, 0.0f, 0.0f)); 
		X_Scale->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		X_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f)); 
	}
	Y_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Scale"));
	Y_Scale->SetupAttachment(MeshComp);
	Y_Scale->ComponentTags.Add(TEXT("Y_Scale"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempY_Scale.Succeeded() )
	{
		Y_Scale->SetStaticMesh(tempY_Scale.Object);
		Y_Scale->SetRelativeLocation(FVector(0.0f, 65.0f, 0.0f));
		Y_Scale->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); 
		Y_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
	}
	Z_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Scale"));
	Z_Scale->SetupAttachment(MeshComp);
	Z_Scale->ComponentTags.Add(TEXT("Z_Scale"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempZ_Scale.Succeeded() )
	{
		Z_Scale->SetStaticMesh(tempZ_Scale.Object);
		Z_Scale->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
		Z_Scale->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); // (Pitch=90.000000,Yaw=0.000000,Roll=0.000000)
		Z_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
	}

}

// Called when the game starts or when spawned
void AAJH_WorldActor::BeginPlay()
{
	Super::BeginPlay();

	GizmoVisibility();
	bIsVisibleLocation = false;
	bIsVisibleRotation = false;
	bIsVisibleScale = false;

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
	X_Scale->SetVisibility(false);
	Y_Scale->SetVisibility(false);
	Z_Scale->SetVisibility(false);
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

	// Scale 축 비활성화
	X_Scale->SetVisibility(false);
	Y_Scale->SetVisibility(false);
	Z_Scale->SetVisibility(false);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("LocationVisibility called"));
}

void AAJH_WorldActor::RotationVisivility()
{
	//bIsAxisLocation = false;
	//bIsAxisRotation = true;

	// Location 축 비활성화
	X_Axis->SetVisibility(false);
	Y_Axis->SetVisibility(false);
	Z_Axis->SetVisibility(false);
	XYZ_Axis->SetVisibility(false);

	// Rotation 축 활성화
	X_Rot->SetVisibility(true);
	Y_Rot->SetVisibility(true);
	Z_Rot->SetVisibility(true);

	// Scale 축 비활성화
	X_Scale->SetVisibility(false);
	Y_Scale->SetVisibility(false);
	Z_Scale->SetVisibility(false);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("RotationVisivility called"));

}

void AAJH_WorldActor::ScaleVisivility()
{
	// Location 축 비활성화
	X_Axis->SetVisibility(false);
	Y_Axis->SetVisibility(false);
	Z_Axis->SetVisibility(false);
	XYZ_Axis->SetVisibility(false);

	// Rotation 축 활성화
	X_Rot->SetVisibility(false);
	Y_Rot->SetVisibility(false);
	Z_Rot->SetVisibility(false);

	// Scale 축 비활성화
	X_Scale->SetVisibility(true);
	Y_Scale->SetVisibility(true);
	Z_Scale->SetVisibility(true);
}

