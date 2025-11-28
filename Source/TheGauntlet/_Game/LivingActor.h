// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageable.h"
#include "LivingActor.generated.h"

UCLASS()
class THEGAUNTLET_API ALivingActor : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALivingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamage_Implementation(float damage);

	UPROPERTY(EditAnywhere, Category = "HP")
	float maxHP;

private:
	float currentHP;
};
