// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TGGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class THEGAUNTLET_API UTGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Level Management")
	void LoadLevel(TSoftObjectPtr<UWorld> level);
};
