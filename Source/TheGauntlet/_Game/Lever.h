// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TGOrderReceiver.h"
#include "Lever.generated.h"


UCLASS()
class THEGAUNTLET_API ALever : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Linked Object")
	TScriptInterface<ITGOrderReceiver> linkedObject;

	void Interact_Implementation(ATheGauntletCharacter* interacter);
	
	UPROPERTY()
	UStaticMeshComponent* TargetMesh;

	// Materiale e Colore
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMat;

	FLinearColor InitialColor;

	FTimerHandle FlashTimerHandle;

	void OnFlashEnded();
};
