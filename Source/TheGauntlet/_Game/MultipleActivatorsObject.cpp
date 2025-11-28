// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/MultipleActivatorsObject.h"

// Sets default values
AMultipleActivatorsObject::AMultipleActivatorsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMultipleActivatorsObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultipleActivatorsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultipleActivatorsObject::DoOrder_Implementation(ALever* activator)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, "Trying opening");
    // 1. Validazione base:
    // La leva deve esistere E deve far parte della lista delle leve richieste (activators)
    if (!activator || !activators.Contains(activator))
    {
        return;
    }

    // 2. Controllo duplicati (Quello che chiedevi)
    // "Se la lista 'activatedActivators' NON contiene già questa leva..."
    if (!activatedActivators.Contains(activator))
    {
        // ...allora aggiungila.
        activatedActivators.Add(activator);

        UE_LOG(LogTemp, Log, TEXT("Leva registrata. Progresso: %d / %d"), activatedActivators.Num(), activators.Num());
    }
    else
    {
        // Opzionale: Se il giocatore clicca su una leva già attivata
        UE_LOG(LogTemp, Warning, TEXT("Questa leva era già stata attivata!"));
        return; // Esci, non serve ricontrollare la vittoria
    }

    // 3. Controllo Vittoria
    // Se il numero di leve attivate è uguale al totale richiesto
    if (activatedActivators.Num() == activators.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("TUTTE LE LEVE ATTIVATE! APERTURA PASSAGGIO."));
        SetActorEnableCollision(false);
        SetActorHiddenInGame(true);
        // Esegui la tua logica di apertura qui
        // OpenDoor();
    }
}

