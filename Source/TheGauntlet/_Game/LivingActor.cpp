// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/LivingActor.h"

#include "HealthComponent.h"

// Sets default values
ALivingActor::ALivingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnDeath.AddDynamic(this, &ALivingActor::DoOnDeath);
}

// Called when the game starts or when spawned
void ALivingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALivingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALivingActor::DoOnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Dead Actor");
	Destroy();
}

