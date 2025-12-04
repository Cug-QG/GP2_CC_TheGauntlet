// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/TGGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UTGGameInstance::LoadLevel(TSoftObjectPtr<UWorld> level)
{
	// Controllo di sicurezza: il nome non deve essere vuoto
	if (!level)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),level);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("errore caricamento livello"));
	}
}
