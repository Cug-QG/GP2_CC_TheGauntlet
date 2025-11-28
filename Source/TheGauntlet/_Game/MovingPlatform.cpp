// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

    StartLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    float NormalizedSin = (FMath::Sin(GetGameTimeSinceCreation() * TimeSpeed) + 1.0f);
    // Ora va da 0 a 1.

    //float HeightDelta = NormalizedSin * (Amplitude);

    FVector NewLocation = StartLocation;
    NewLocation.Z += NormalizedSin * Amplitude;

    SetActorLocation(NewLocation);

}

