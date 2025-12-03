// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheGauntletGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVictory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLost);
UCLASS(abstract)
class ATheGauntletGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ATheGauntletGameMode();
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnVictory OnVictoryEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void TriggerLevelVictory();
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLost OnLostEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void TriggerLost();
};



