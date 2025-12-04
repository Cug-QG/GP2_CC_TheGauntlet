// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	
}

void UHealthComponent::HandleTakeDamage(float DamageAmount)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "taking damage");
	
	if(CurrentHealth <= 0) return;

	CurrentHealth -= DamageAmount;
	OnDamage.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Salute rimanente: %f"), CurrentHealth);
	
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
}

