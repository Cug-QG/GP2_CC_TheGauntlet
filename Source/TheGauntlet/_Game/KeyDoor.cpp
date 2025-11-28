// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/KeyDoor.h"

// Sets default values
AKeyDoor::AKeyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeyDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyDoor::Interact_Implementation(ATheGauntletCharacter* interacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Being Interacted");

	if (interacter->hasKey == true) { Destroy(); }
}

