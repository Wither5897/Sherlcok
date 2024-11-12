// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/CustomizingCharacter.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACustomizingCharacter::ACustomizingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);

	CoatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Coat Mesh Component"));
	CoatMesh->SetupAttachment(GetMesh());

	HatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh Component"));
	HatMesh->SetupAttachment(GetMesh());
	HatMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hatSocket"));
}

// Called when the game starts or when spawned
void ACustomizingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomizingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomizingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomizingCharacter::SetCoatMaterial(class UMaterial* Material){
	CoatMesh->SetMaterial(0, Material);
}

void ACustomizingCharacter::SetHatMaterial(class UMaterial* Material){
	for (int32 i = 0; i < 4; i++){
		HatMesh->SetMaterial(i, Material);
	}
}

