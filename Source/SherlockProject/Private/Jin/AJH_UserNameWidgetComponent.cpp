// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_UserNameWidgetComponent.h"
#include "Jin/AJH_UserNameTagWidget.h"
#include "AJH_SherlockGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UAJH_UserNameWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

	// 약간의 딜레이 후에 컨트롤러 확인
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UAJH_UserNameWidgetComponent::CheckPlayerController, 0.5f, false);

}

void UAJH_UserNameWidgetComponent::ServerSetUserName_Implementation(const FString& UserName_)
{
	UserName = UserName_;
	MultiCastSetUserName(UserName);
}

void UAJH_UserNameWidgetComponent::MultiCastSetUserName_Implementation(const FString& UserName_)
{
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

				pc = UGameplayStatics::GetPlayerController(World, 0);
				if ( GetOwner() && pc->IsLocalController() )
				{
					// 게임 인스턴스에서 닉네임을 받아 캐릭터에 설정
					ServerSetUserName(GameInstance->UserNickName);
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
