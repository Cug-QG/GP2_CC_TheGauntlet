// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGauntletGameMode.h"

ATheGauntletGameMode::ATheGauntletGameMode()
{
	// stub
}

void ATheGauntletGameMode::TriggerLevelVictory()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Victory");
	
	OnVictoryEvent.Broadcast();
}

void ATheGauntletGameMode::TriggerLost()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Lost");
	
	OnLostEvent.Broadcast();
}

