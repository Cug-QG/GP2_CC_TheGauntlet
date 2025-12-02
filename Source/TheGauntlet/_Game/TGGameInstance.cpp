// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/TGGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UTGGameInstance::LoadLevel(FName LevelName)
{
	// Controllo di sicurezza: il nome non deve essere vuoto
	if (!LevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("errore caricamento livello"));
	}
}
