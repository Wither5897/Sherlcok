
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "SK/ItemWidget.h"
#include "Components/Button.h"
#include "SK/ReportWidget.h"
#include "UW_ReportBoard.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_ReportBoard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportB;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportB1;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportB2;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportB3;

	UPROPERTY(meta = (BindWidget ))
	class UButton* OpenReportB4;


	UPROPERTY(meta = ( BindWidget ))
	class UBackgroundBlur* BackgroundBlur_1;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* FirstReport;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* HandReport;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* WitnessReport;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ExpertReport;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* AutopsyReport;

	UFUNCTION()
	void OpenEvidence1();

	UFUNCTION()
	void OpenEvidence2();

	UFUNCTION()
	void OpenEvidence3();

	UFUNCTION()
	void OpenEvidence4();

	UFUNCTION()
	void OpenEvidence();


	UFUNCTION()
	void CloseButtonClicked();

	UPROPERTY()
	TArray<UReportWidget*> Reports;
};
