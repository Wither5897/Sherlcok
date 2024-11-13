// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CreatorToolTravelActor.h"
#include "Components/BoxComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Jin/AJH_CreatorToolTravel.h"
#include "SherlockPlayerController.h"

// Sets default values
AAJH_CreatorToolTravelActor::AAJH_CreatorToolTravelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TravelboxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TravelboxComp"));
	SetRootComponent(TravelboxComp);

}

// Called when the game starts or when spawned
void AAJH_CreatorToolTravelActor::BeginPlay()
{
	Super::BeginPlay();
	
	TravelboxComp->OnComponentBeginOverlap.AddDynamic(this, &AAJH_CreatorToolTravelActor::OnMyBeginOverlap);
	TravelboxComp->OnComponentEndOverlap.AddDynamic(this, &AAJH_CreatorToolTravelActor::OnMyEndOverlap);
	pc = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AAJH_CreatorToolTravelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_CreatorToolTravelActor::OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<ATP_ThirdPersonCharacter>(OtherActor);

	if (player && player->IsLocallyControlled() )
	{
		player->CreatorToolTravel->SetVisibility(ESlateVisibility::Visible);
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
}

void AAJH_CreatorToolTravelActor::OnMyEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	player = Cast<ATP_ThirdPersonCharacter>(OtherActor);

	if (player && player->IsLocallyControlled() )
	{
		player->CreatorToolTravel->SetVisibility(ESlateVisibility::Collapsed);
		pc->bShowMouseCursor = false;
		pc->SetInputMode(FInputModeGameOnly());
	}
}

