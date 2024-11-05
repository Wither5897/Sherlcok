// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorActor.h"

// Sets default values
AAJH_EditorActor::AAJH_EditorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AAJH_EditorActor::BeginPlay()
{
	Super::BeginPlay();
	
	pc = GetWorld()->GetFirstPlayerController();

}

// Called every frame
void AAJH_EditorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float ScreenX, ScreenY;
	pc->GetMousePosition(ScreenX, ScreenY);

	FVector WorldLocation, WorldDirection;
	if ( pc->DeprojectScreenPositionToWorld(ScreenX, ScreenY, WorldLocation, WorldDirection) )
	{
		FVector Start = WorldLocation;
		FVector End = WorldLocation + ( WorldDirection * 5000.0f ); // 5000 units trace distance

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility,
			FCollisionQueryParams(FName(TEXT("MouseTrace")), true, this)
		);

		// Visual debugging aid
		// DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

		if ( bHit && HitResult.bBlockingHit )
		{
			// If hit, set actor location to the hit location
			SetActorLocation(HitResult.Location);
		}
		else
		{
			FVector TargetLocation = WorldLocation + ( WorldDirection * 1000.0f ); // Move 1000 units in direction
			SetActorLocation(TargetLocation);
		}
	}

}

