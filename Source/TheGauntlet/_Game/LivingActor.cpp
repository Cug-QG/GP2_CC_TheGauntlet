// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/LivingActor.h"

// Sets default values
ALivingActor::ALivingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALivingActor::BeginPlay()
{
	Super::BeginPlay();
	currentHP = maxHP;
}

// Called every frame
void ALivingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALivingActor::TakeDamage_Implementation(float damage) 
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, "Taking damage");

	currentHP -= damage;

	if (currentHP <= 0) { Destroy(); }
}

