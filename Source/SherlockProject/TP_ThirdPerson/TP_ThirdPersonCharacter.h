// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Components/ArrowComponent.h"
#include "Components/ChildActorComponent.h"
#include "EvidenceActor.h"
#include "KHH_InteractionWidget.h"
#include "Components/TimelineComponent.h"
#include "HighLightInterface.h"
#include "UW_Notify.h"
#include "TP_ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UChildActorComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotLight;
	
	UPROPERTY()
	class AEvidenceActor* EvidenceActor;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = ( AllowPrivateAccess = "true" ))
	UInputAction* IA_Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = ( AllowPrivateAccess = "true" ))
	UInputAction* IA_OpenInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = ( AllowPrivateAccess = "true" ))
	UInputAction* IA_FlashLight;
	
	//widget====================================================================================================

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UKHH_InteractionWidget> interactionUIsetting;

	UPROPERTY()
	class UKHH_InteractionWidget* interactionUI;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> InventoryUIFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UInventoryWidget* InventoryUI;

	
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> reportboardUI;

	UPROPERTY(BlueprintReadOnly)
	class UUW_ReportBoard* reportboard;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> SummaryWidgetFactory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAJH_SummaryWidget* SummaryWidget;

	//====================================================================================================
	
	FVector Startlocation;
	FVector EndArrowlocation;

	// =============================

public:
	ATP_ThirdPersonCharacter();

	void OnMyActionZoomIn();
	void OnMyActionZoomOut();

	void PerformHighLight();

	void OnOffFlashLight();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float TargetFOV = 90;

	void Interaction();

	UFUNCTION(server, Reliable)
	void ServerItemFound(int32 ActorNum, int32 PlayerID);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastItemFound(int32 ActorNum, int32 PlayerID);
	
	void PerformLineTrace();

	void OpenInventory();

	FHitResult OutHit;
	FVector start;
	FVector End;
	ECollisionChannel traceChannel;
	FCollisionQueryParams Params;
	bool bHit = false;
	bool bPick = false;

	float tracedis = 200;

	UPROPERTY()
	class UHighlightComponent* Comp;

	UPROPERTY()
	TArray<UStaticMeshComponent*> OutputMeshComp;


	UPROPERTY()
	TArray<bool>check;

	bool isNotify1Checked = false;
	bool isNotify2Checked = false;
	bool isNotify3Checked = false;
	bool isNotify4Checked = false;

};

