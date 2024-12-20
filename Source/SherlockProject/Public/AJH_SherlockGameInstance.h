﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SK/MapSaveGame.h"
#include "AJH_SherlockGameInstance.generated.h"

/**
 * 
 */

class ATP_ThirdPersonCharacter;

USTRUCT(BlueprintType)
struct FCustomizingData{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoatIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HatIdx;

	FCustomizingData() : CoatIdx(0), HatIdx(0) {}
};

UCLASS()
class SHERLOCKPROJECT_API UAJH_SherlockGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	IOnlineSessionPtr sessionInterface;
	//세션에 관련된 모든 컨트롤을 하는 기본클래스
	
	UFUNCTION(BlueprintCallable)
	void CreateMySession();		// 요청한 결과를 받기 위한 함수
	UFUNCTION(BlueprintCallable)
	void FindMySession();
	void JoinMySession(int32 roomNumber);
	void ExitMySession();
	void SetSessionName(FString name, FString ClickedroomName_, FString ClickedhostName_, int32 ClickedplayerCount_);
	FORCEINLINE FString GetSessionName() { return mySessionName.ToString(); }

	void CreateOrFindMySession();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	// FString ClickedroomName = FString("Crime_Scene");
	FString ClickedroomName = FString("CUBIC");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FString ClickedhostName= FString("Crime_Host");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 ClickedplayerCount=4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	FString UserNickName="None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 meshNum;
	void UserNickNameToCharacter(ACharacter* player);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TArray<FName> AllSessionNames;
	void OnDestroyAllSessions();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	UMapSaveGame* LoadGameInstance;
	
	UFUNCTION(BlueprintCallable)
	void SaveLevel(FString LevelName, FText IntroTitle, FText IntroContext, FText OutroStory);

	UFUNCTION(BlueprintCallable)
	void LoadLevel(FString LevelName);

	UFUNCTION(BlueprintCallable)
	void SaveSimulationSlot();

	UFUNCTION(BlueprintCallable)
	void LoadSimulationSlot();
	
	UFUNCTION(BlueprintCallable)
	void OnCharacterReady(ATP_ThirdPersonCharacter* Character);
	
	bool bShouldLoadLevel = false;

	FString LoadLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TArray<FCustomizingData> CustomizingDataArray;

	UPROPERTY()
	bool bIsSoundOn = false;

	UPROPERTY()
	TArray<float> PlayerCollection;

	FLevelSaveData CachedLevelData;

	float NewSKHeight = 0.f;
private:
	FName mySessionName = FName("first Session");
	TSharedPtr<class FOnlineSessionSearch> sessionSearch;	//OnlineSessionSearch 는 
	
	void OnCreatedSession(FName sessionName, bool bWasSuccessful);	//서버에 세션생성을 요청하기 위한 함수
	void OnFoundSession(bool bwasSuccessful);
	void OnJoinedSession(FName SesssionName, EOnJoinSessionCompleteResult::Type result);
	void OnDestroyedSesssion(FName sessionName, bool bwasSuccessful);

};
