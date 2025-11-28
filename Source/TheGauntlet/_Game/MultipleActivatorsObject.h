// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TGOrderReceiver.h"

#include "MultipleActivatorsObject.generated.h"

UCLASS()
class THEGAUNTLET_API AMultipleActivatorsObject : public AActor, public ITGOrderReceiver
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultipleActivatorsObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoOrder_Implementation(ALever* activator);

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<ALever*> activators;

	TArray<ALever*> activatedActivators;
};
