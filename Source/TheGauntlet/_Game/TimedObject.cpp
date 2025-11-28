// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/TimedObject.h"

// Sets default values
ATimedObject::ATimedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimedObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimedObject::DoOrder_Implementation(ALever* activator)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Activated");

    Open();

    // 2. Gestione Timer
    // Otteniamo il TimerManager del mondo
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();

    // Se c'è già un timer attivo (es. il giocatore ha premuto due volte), lo puliamo
    if (TimerManager.IsTimerActive(TimerHandle_CloseDoor))
    {
        TimerManager.ClearTimer(TimerHandle_CloseDoor);
    }

    // 3. Imposta il nuovo timer
    // Parametri: Handle, Oggetto(this), Funzione da chiamare, Tempo, Loop(false)
    TimerManager.SetTimer(
        TimerHandle_CloseDoor,
        this,
        &ATimedObject::Close,
        timer,
        false
    );
}

void ATimedObject::Open()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, "Opened");
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ATimedObject::Close()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, "Closed");
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

