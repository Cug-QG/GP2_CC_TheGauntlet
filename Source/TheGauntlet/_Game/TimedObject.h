// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TGOrderReceiver.h"

#include "TimedObject.generated.h"

UCLASS()
class THEGAUNTLET_API ATimedObject : public AActor, public ITGOrderReceiver
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimedObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float timer;

	FTimerHandle TimerHandle_CloseDoor;

	void DoOrder_Implementation(ALever* activator);

	void Open();
	void Close();
};
