// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_WorldActor.h"
#include "Components/SceneComponent.h"
#include "Jin/AJH_ExPlainBtnWidget.h"
#include "UW_EditorExplain.h"

// Sets default values
AAJH_WorldActor::AAJH_WorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GizmoRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GizmoRoot"));
	SetRootComponent(GizmoRoot);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(GizmoRoot);
	Tags.Add(TEXT("Actor"));
	// Tags.Add(TEXT("InteractObj"));
	X_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Axis"));
	X_Axis->SetupAttachment(GizmoRoot);
	X_Axis->ComponentTags.Add(TEXT("X_Axis"));
	X_Axis->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempX_Axis.Succeeded() )
	{
		X_Axis->SetStaticMesh(tempX_Axis.Object);
		X_Axis->SetRelativeLocation(FVector(30.0f, 0.0f,0.0f));
		X_Axis->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		X_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	Y_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Axis"));
	Y_Axis->SetupAttachment(GizmoRoot);
	Y_Axis->ComponentTags.Add(TEXT("Y_Axis"));
	Y_Axis->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempY_Axis.Succeeded() )
	{
		Y_Axis->SetStaticMesh(tempY_Axis.Object);
		Y_Axis->SetRelativeLocation(FVector(0.0f, 30.0f, 0.0f));
		Y_Axis->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		Y_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	Z_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Axis"));
	Z_Axis->SetupAttachment(GizmoRoot);
	Z_Axis->ComponentTags.Add(TEXT("Z_Axis"));
	Z_Axis->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Axis(TEXT("'/Game/Jin/Mesh/AJH_GizMoArrowHandle.AJH_GizMoArrowHandle'"));
	if ( tempZ_Axis.Succeeded() )
	{
		Z_Axis->SetStaticMesh(tempZ_Axis.Object);
		Z_Axis->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f)); 
		Z_Axis->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); 
		Z_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f)); 
	}
	XYZ_Axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XYZ_Axis"));
	XYZ_Axis->SetupAttachment(GizmoRoot);
	XYZ_Axis->ComponentTags.Add(TEXT("XYZ_Axis"));
	XYZ_Axis->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempXYZ_Axis(TEXT("'/Engine/VREditor/TransformGizmo/UniformScaleHandle.UniformScaleHandle'"));
	if ( tempXYZ_Axis.Succeeded() )
	{
		XYZ_Axis->SetStaticMesh(tempXYZ_Axis.Object);
		XYZ_Axis->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); 
		XYZ_Axis->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); 
		XYZ_Axis->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f)); 
	}
	X_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Rot"));
	X_Rot->SetupAttachment(GizmoRoot);
	X_Rot->ComponentTags.Add(TEXT("X_Rot"));
	X_Rot->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempX_Rot.Succeeded() )
	{
		X_Rot->SetStaticMesh(tempX_Rot.Object);
		X_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		X_Rot->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		X_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	Y_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Rot"));
	Y_Rot->SetupAttachment(GizmoRoot);
	Y_Rot->ComponentTags.Add(TEXT("Y_Rot"));
	Y_Rot->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempY_Rot.Succeeded() )
	{
		Y_Rot->SetStaticMesh(tempY_Rot.Object);
		Y_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Y_Rot->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Y_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	Z_Rot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Rot"));
	Z_Rot->SetupAttachment(GizmoRoot);
	Z_Rot->ComponentTags.Add(TEXT("Z_Rot"));
	Z_Rot->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Rot(TEXT("'/Engine/VREditor/TransformGizmo/RotationHandleQuarter.RotationHandleQuarter'"));
	if ( tempZ_Rot.Succeeded() )
	{
		Z_Rot->SetStaticMesh(tempZ_Rot.Object);
		Z_Rot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Z_Rot->SetRelativeRotation(FRotator(-90.0f, 360.0f, 0.0f)); 
		Z_Rot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	X_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X_Scale"));
	X_Scale->SetupAttachment(GizmoRoot);
	X_Scale->ComponentTags.Add(TEXT("X_Scale"));
	X_Scale->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempX_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempX_Scale.Succeeded() )
	{
		X_Scale->SetStaticMesh(tempX_Scale.Object);
		X_Scale->SetRelativeLocation(FVector(65.0f, 0.0f, 0.0f)); 
		X_Scale->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		X_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f)); 
	}
	Y_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Y_Scale"));
	Y_Scale->SetupAttachment(GizmoRoot);
	Y_Scale->ComponentTags.Add(TEXT("Y_Scale"));
	Y_Scale->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempY_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempY_Scale.Succeeded() )
	{
		Y_Scale->SetStaticMesh(tempY_Scale.Object);
		Y_Scale->SetRelativeLocation(FVector(0.0f, 65.0f, 0.0f));
		Y_Scale->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); 
		Y_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
	}
	Z_Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Z_Scale"));
	Z_Scale->SetupAttachment(GizmoRoot);
	Z_Scale->ComponentTags.Add(TEXT("Z_Scale"));
	Z_Scale->bCastDynamicShadow = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempZ_Scale(TEXT("'/Engine/VREditor/TransformGizmo/BoundingBoxEdge.BoundingBoxEdge'"));
	if ( tempZ_Scale.Succeeded() )
	{
		Z_Scale->SetStaticMesh(tempZ_Scale.Object);
		Z_Scale->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
		Z_Scale->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f)); // (Pitch=90.000000,Yaw=0.000000,Roll=0.000000)
		Z_Scale->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
	}

	// ======================Material==============================
	ConstructorHelpers::FObjectFinder<UMaterial> tempX_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/X_Mat.X_Mat'"));
	ConstructorHelpers::FObjectFinder<UMaterial> tempGizmoX_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/Gizmo_X_Mat.Gizmo_X_Mat'"));
	if ( tempX_Mat.Succeeded() && tempGizmoX_Mat.Succeeded() )
	{
		X_Axis->SetMaterial(0, tempX_Mat.Object);
		X_Axis->SetMaterial(1, tempGizmoX_Mat.Object);
		X_Rot->SetMaterial(0, tempX_Mat.Object);
		X_Rot->SetMaterial(1, tempGizmoX_Mat.Object);
		X_Scale->SetMaterial(0, tempX_Mat.Object);
		X_Scale->SetMaterial(1, tempGizmoX_Mat.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> temY_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/Y_Mat.Y_Mat'"));
	ConstructorHelpers::FObjectFinder<UMaterial> tempGizmoY_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/Gizmo_Y_Mat.Gizmo_Y_Mat'"));
	if ( temY_Mat.Succeeded() && tempGizmoY_Mat.Succeeded() )
	{
		Y_Axis->SetMaterial(0, temY_Mat.Object);
		Y_Axis->SetMaterial(1, tempGizmoY_Mat.Object);
		Y_Rot->SetMaterial(0, temY_Mat.Object);
		Y_Rot->SetMaterial(1, tempGizmoY_Mat.Object);
		Y_Scale->SetMaterial(0, temY_Mat.Object);
		Y_Scale->SetMaterial(1, tempGizmoY_Mat.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> temZ_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/Z_Mat.Z_Mat'"));
	ConstructorHelpers::FObjectFinder<UMaterial> tempGizmoZ_Mat(TEXT("/Script/Engine.Material'/Game/Jin/Material/Gizmo_Z_Mat.Gizmo_Z_Mat'"));
	if ( temZ_Mat.Succeeded() && tempGizmoZ_Mat.Succeeded() )
	{
		Z_Axis->SetMaterial(0, temZ_Mat.Object);
		Z_Axis->SetMaterial(1, tempGizmoZ_Mat.Object);
		Z_Rot->SetMaterial(0, temZ_Mat.Object);
		Z_Rot->SetMaterial(1, tempGizmoZ_Mat.Object);
		Z_Scale->SetMaterial(0, temZ_Mat.Object);
		Z_Scale->SetMaterial(1, tempGizmoZ_Mat.Object);
	}

	ConstructorHelpers::FClassFinder<UAJH_ExPlainBtnWidget> tempExPlain(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Jin/UI/WBP_ExPlainBtn.WBP_ExPlainBtn_C'"));
	if ( tempExPlain.Succeeded() )
	{
		ExPlainBtnFactory = tempExPlain.Class;
	}
	ConstructorHelpers::FClassFinder<UUW_EditorExplain> tempEditorExplain(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/WBP_EditorExplain.WBP_EditorExplain_C'"));
	if ( tempEditorExplain.Succeeded() )
	{
		EditorExplainFactory = tempEditorExplain.Class;
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

	// 충돌 채널 초기화
	X_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Y_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Z_Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	ExPlainBtnWidget = Cast<UAJH_ExPlainBtnWidget>(CreateWidget(GetWorld(), ExPlainBtnFactory));
	if ( ExPlainBtnWidget )
	{
		ExPlainBtnWidget->AddToViewport();
		ExPlainBtnWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	EditorExplain = Cast<UUW_EditorExplain>(CreateWidget(GetWorld(), EditorExplainFactory));
	if ( EditorExplain )
	{
		EditorExplain->AddToViewport();
		EditorExplain->SetVisibility(ESlateVisibility::Collapsed);
	}

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

	ExPlainBtnWidget->SetVisibility(ESlateVisibility::Visible);
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

	ExPlainBtnWidget->SetVisibility(ESlateVisibility::Visible);
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

	ExPlainBtnWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAJH_WorldActor::OnFixGizmoRotation()
{
	if ( GizmoRoot )
	{
		GizmoRoot->SetRelativeRotation(FRotator::ZeroRotator);
	}
}

void AAJH_WorldActor::OnFixGizmoScale()
{
	if ( GizmoRoot )
	{
		GizmoRoot->SetRelativeScale3D(FVector::ZeroVector);
	}
}

void AAJH_WorldActor::OnExPlainBtn()
{
	
}

