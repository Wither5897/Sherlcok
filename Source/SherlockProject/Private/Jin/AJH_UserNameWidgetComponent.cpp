// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_UserNameWidgetComponent.h"
#include "Jin/AJH_UserNameTagWidget.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SherlockPlayerController.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

UAJH_UserNameWidgetComponent::UAJH_UserNameWidgetComponent()
{
	// 컴포넌트가 생성될 때 복제 설정
	SetIsReplicatedByDefault(true);
}

void UAJH_UserNameWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

	pc = Cast<ASherlockPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 약간의 딜레이 후에 컨트롤러 확인
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UAJH_UserNameWidgetComponent::CheckPlayerController, 0.5f, false);
	AActor* OwnerActor = GetOwner();
	if (  OwnerActor )
	{
		ATP_ThirdPersonCharacter* me = Cast<ATP_ThirdPersonCharacter>(OwnerActor);
		if ( me )
		{
			pc = Cast<ASherlockPlayerController>(me->GetController());
			if(pc && pc->HasAuthority())
			{
				UE_LOG(LogTemp, Warning, TEXT("UAJH_UserNameWidgetComponent is running on the server"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UAJH_UserNameWidgetComponent is running on the client"));
			}
		}
	}
}

void UAJH_UserNameWidgetComponent::ServerSetUserName_Implementation(const FString& UserName_)
{
	UserName = UserName_;
	UE_LOG(LogTemp, Warning, TEXT("ServerSetUserName called with UserName: %s"), *UserName_);
	MultiCastSetUserName(UserName);
}

void UAJH_UserNameWidgetComponent::MultiCastSetUserName_Implementation(const FString& UserName_)
{
	UE_LOG(LogTemp, Warning, TEXT("MultiCastSetUserName called with UserName: %s"), *UserName_);
	SetUserName(UserName_);
}

void UAJH_UserNameWidgetComponent::OnRep_UserName()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep_UserName called with UserName: %s"), *UserName);
	SetUserName(UserName);
}

void UAJH_UserNameWidgetComponent::CheckPlayerController()
{
	UWorld* World = GetWorld();
	if ( World )
	{
		UAJH_SherlockGameInstance* GameInstance = Cast<UAJH_SherlockGameInstance>(World->GetGameInstance());
		if ( GameInstance )
		{
			if ( AActor* ownerActor = GetOwner() )
			{
				pc = Cast<ASherlockPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
				if ( GetOwner() && pc->IsLocalController() )
				{
					UE_LOG(LogTemp, Warning, TEXT("Client is calling ServerSetUserName with UserName: %s"), *GameInstance->UserNickName);
					// 게임 인스턴스에서 닉네임을 받아 캐릭터에 설정
					pc->ServerSetUserName(GameInstance->UserNickName);

					UE_LOG(LogTemp, Warning, TEXT("Client called ServerSetUserName"));
				}
			}
		}

	}
}

void UAJH_UserNameWidgetComponent::SetUserName(FString UserName_)
{
    UAJH_UserNameTagWidget* UserNameWidget = Cast<UAJH_UserNameTagWidget>(GetUserWidgetObject());
    if ( UserNameWidget )
    {
        UserNameWidget->SetUserName(UserName_);
    }
}

void UAJH_UserNameWidgetComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 필요한 모든 변수가 네트워크에서 복제되도록 설정
	DOREPLIFETIME(UAJH_UserNameWidgetComponent, UserName);
}
