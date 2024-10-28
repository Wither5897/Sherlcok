
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "SK/ItemWidget.h"
#include "Components/Button.h"
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
	class UButton* OpenReportButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenReportButton_3;

	UPROPERTY(meta = (BindWidget ))
	class UButton* OpenReportButton_4;


	UPROPERTY(meta = ( BindWidget ))
	class UBackgroundBlur* BackgroundBlur_1;

	UPROPERTY(EditDefaultsOnly, meta = ( BindWidget ))
	class UWidgetSwitcher* WidgetSwitcher_1;


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
	void OpenEvidence();

	UFUNCTION()
	void CloseButtonClicked();
};
