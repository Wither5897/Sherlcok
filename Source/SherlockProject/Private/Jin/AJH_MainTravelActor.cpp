// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_MainTravelActor.h"
#include "Components/BoxComponent.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_CrimeSceneTravelWidget.h"
#include "Jin/AJH_TravelClientWidget.h"
#include "SherlockPlayerController.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AAJH_MainTravelActor::AAJH_MainTravelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mainTravelBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MainTravelBoxComp"));
	SetRootComponent(mainTravelBoxComp);

}

// Called when the game starts or when spawned
void AAJH_MainTravelActor::BeginPlay()
{
	Super::BeginPlay();
	
	// mainTravelBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AAJH_MainTravelActor::OnMyMainTravelBoxBeginOverlap);
	// mainTravelBoxComp->OnComponentEndOverlap.AddDynamic(this, &AAJH_MainTravelActor::OnMyMainTravelBoxEndOverlap);
	pc = Cast<ASherlockPlayerController>(GetWorld()->GetFirstPlayerController());

}

// Called every frame
void AAJH_MainTravelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_MainTravelActor::ShowCrimeSceneTravelWidget_Server(AActor* OtherActor)
{
	
}

void AAJH_MainTravelActor::ShowCrimeSceneTravelWidget_Client(AActor* OtherActor)
{
	
}

void AAJH_MainTravelActor::OnMyMainTravelBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<ATP_ThirdPersonCharacter>(OtherActor);
	if ( player && player->IsLocallyControlled() && player->HasAuthority() )
	{
		player->CrimeSceneTravelWidget->SetVisibility(ESlateVisibility::Visible);
		player->CrimeSceneTravelWidget->OnMyAnim_Switcherindex();
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
	else if( player && player->IsLocallyControlled())
	{
		player->TravelClientWidget->SetVisibility(ESlateVisibility::Visible);
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
}

void AAJH_MainTravelActor::OnMyMainTravelBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	player = Cast<ATP_ThirdPersonCharacter>(OtherActor);
	if ( player && player->IsLocallyControlled() && player->HasAuthority() )
	{
		player->CrimeSceneTravelWidget->SetVisibility(ESlateVisibility::Collapsed);
		pc->bShowMouseCursor = false;
		pc->SetInputMode(FInputModeGameOnly());
	}
	else if ( player && player->IsLocallyControlled() )
	{
		player->TravelClientWidget->SetVisibility(ESlateVisibility::Collapsed);
		pc->bShowMouseCursor = false;
		pc->SetInputMode(FInputModeGameOnly());
	}
}

