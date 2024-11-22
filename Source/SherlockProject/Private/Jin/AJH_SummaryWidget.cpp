// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_SummaryWidget.h"

#include <string>

#include "Components/Button.h"
#include "SK/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "AJH_SherlockGameInstance.h"
#include "Engine/Engine.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "SK/MultiPlayerState.h"
#include "SK/StatisticsWidget.h"

void UAJH_SummaryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if ( !me ) {
		return;
	}
	InventoryUI = me->InventoryUI;

	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	FString PlayerName = gi->UserNickName;

	auto* ps = me->GetPlayerState();
	if ( ps->GetPlayerId() == 0 ) {
		// Player1Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 1 ) {
		// Player2Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 2 ) {
		// Player3Name->SetText(FText::FromString(PlayerName));
	}

	if ( Btn_Submit )
	{
		Btn_Submit->OnClicked.AddDynamic(this, &UAJH_SummaryWidget::OnMyBtn_Click);
	}
	LoadClueData();
}

void UAJH_SummaryWidget::OnSuspectImage(class UTexture2D* SavedTexture, int32 playerid)
{
	if ( !Img_SuspectImage1 ) {
		return;
	}
	Img_SuspectImage1->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnWeaponImage(class UTexture2D* SavedTexture, int32 playerid)
{
	if ( !Img_WeaponImage1 ) {
		return;
	}
	Img_WeaponImage1->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMainEvidenceImage(class UTexture2D* SavedTexture, int32 playerid)
{
	if ( !Img_MainEvidenceImage1 ) {
		return;
	}
	Img_MainEvidenceImage1->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnSpecialThingImage(class UTexture2D* SavedTexture, int32 playerid)
{
	if ( !Img_SpecialThingImage1 ) {
		return;
	}
	Img_SpecialThingImage1->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMyBtn_Click(){
	if (ClueDataArray.Num() == 0)
	{
		LoadClueData();
	}
	
	// alltexture 배열을 순회하면서 비교합니다
	for (int32 i = 0; i < AllTexture.Num(); i++)
	{
		// 각 이미지와 현재 alltexture 요소를 비교하고, 일치하면 다음 Clue의 해당 카테고리 카운트를 증가
		if (Img_SuspectImage1->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[i].SuspectCount++;
		}
        
		if (Img_WeaponImage1->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[i].WeaponCount++;
		}
        
		if (Img_MainEvidenceImage1->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[i].MainEvidenceCount++;
		}
        
		if (Img_SpecialThingImage1->GetBrush().GetResourceObject() == AllTexture[i])
		{
			ClueDataArray[i].SpecialThingCount++;
		}
	}
	SaveClueData();
	SetVisibility(ESlateVisibility::Hidden);
	me->StatisticsUI->SetVisibility(ESlateVisibility::Visible);
}

void UAJH_SummaryWidget::LoadClueData(){
	// JSON 파일 경로 설정
	FString JsonFilePath = FPaths::ProjectDir() / TEXT("GameData") /  TEXT("Clue.json");
	FString JsonString;

	// JSON 파일 읽기
	if (FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// "data" 배열 가져오기
			TArray<TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField(TEXT("data"));

			// ClueDataArray 초기화
			ClueDataArray.Empty();

			// 각 데이터 항목을 파싱하여 ClueDataArray에 추가
			for (auto& JsonValue : DataArray)
			{
				TSharedPtr<FJsonObject> ClueObject = JsonValue->AsObject();
				FClueData ClueData;

				ClueData.ClueID = ClueObject->GetStringField(TEXT("ClueID"));
				ClueData.SuspectCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("SuspectCount")));
				ClueData.WeaponCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("WeaponCount")));
				ClueData.MainEvidenceCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("MainEvidenceCount")));
				ClueData.SpecialThingCount = FCString::Atoi(*ClueObject->GetStringField(TEXT("SpecialThingCount")));

				ClueDataArray.Add(ClueData);
			}

			// 데이터 로드 확인을 위한 디버그 출력
			UE_LOG(LogTemp, Warning, TEXT("Successfully loaded %d clue entries"), ClueDataArray.Num());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON data"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file from path: %s"), *JsonFilePath);
	}
}

void UAJH_SummaryWidget::SaveClueData(){
	for (int32 i = 0; i < ClueDataArray.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Saving Clue %d - Suspect: %d, Weapon: %d, Evidence: %d, Special: %d"),
			i,
			ClueDataArray[i].SuspectCount,
			ClueDataArray[i].WeaponCount,
			ClueDataArray[i].MainEvidenceCount,
			ClueDataArray[i].SpecialThingCount);
	}
	// 저장 경로를 GameSavedDir로 변경
	FString JsonFilePath = FPaths::ProjectDir() / TEXT("GameData") /  TEXT("Clue.json");

	// 디렉토리가 없다면 생성
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*FPaths::GetPath(JsonFilePath)))
	{
		PlatformFile.CreateDirectoryTree(*FPaths::GetPath(JsonFilePath));
	}    
	// 최상위 JSON 객체 생성
	TSharedPtr<FJsonObject> MainJsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonObject>> DataArray;
    
	// ClueDataArray의 각 항목을 JSON 객체로 변환
	for (const FClueData& ClueData : ClueDataArray)
	{
		TSharedPtr<FJsonObject> JsonClue = MakeShareable(new FJsonObject);
        
		// 데이터 설정
		JsonClue->SetStringField(TEXT("ClueID"), ClueData.ClueID);
		JsonClue->SetStringField(TEXT("SuspectCount"), FString::FromInt(ClueData.SuspectCount));
		JsonClue->SetStringField(TEXT("WeaponCount"), FString::FromInt(ClueData.WeaponCount));
		JsonClue->SetStringField(TEXT("MainEvidenceCount"), FString::FromInt(ClueData.MainEvidenceCount));
		JsonClue->SetStringField(TEXT("SpecialThingCount"), FString::FromInt(ClueData.SpecialThingCount));
        
		DataArray.Add(JsonClue);
	}
    
	// 데이터 배열을 메인 JSON 객체에 추가
	TArray<TSharedPtr<FJsonValue>> JsonValueArray;
	for (const TSharedPtr<FJsonObject>& JsonClue : DataArray)
	{
		JsonValueArray.Add(MakeShareable(new FJsonValueObject(JsonClue)));
	}
	MainJsonObject->SetArrayField(TEXT("data"), JsonValueArray);
    
	// JSON 문자열로 변환
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(MainJsonObject.ToSharedRef(), Writer);
    
	// 파일에 저장
	if (FFileHelper::SaveStringToFile(OutputString, *JsonFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully saved clue data to JSON file"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save clue data to JSON file"));
	}
}
