// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/HighlightComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UHighlightComponent::UHighlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UHighlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHighlightComponent::SKHighlight(TArray<class UStaticMeshComponent*> Target)
{
	if ( Target.Num() <= 0 ) {
		return;
	}
	for ( auto* key : Target ) {
		if ( IsValid(key) ) {
			key->SetRenderCustomDepth(true);
			key->SetCustomDepthStencilValue(2);
		}
	}
}

void UHighlightComponent::SKUnHighlight(TArray<class UStaticMeshComponent*> Target)
{
	if ( Target.Num() <= 0 ) {
		return;
	}
	for ( auto* key : Target ) {
		if ( IsValid(key) ) {
			key->SetRenderCustomDepth(false);
			key->SetCustomDepthStencilValue(0);
		}
	}
}
