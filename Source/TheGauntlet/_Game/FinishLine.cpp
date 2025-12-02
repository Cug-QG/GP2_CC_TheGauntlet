// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/FinishLine.h"

#include "TheGauntletCharacter.h"
#include "TheGauntletGameMode.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
	// AMyGameMode* GM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
 //    
	// if (GM)
	// {
	// 	// Iscriviamo la funzione del GameMode al nostro delegate
	// 	OnVictoryEvent.AddDynamic(GM, &AMyGameMode::OnLevelCompleted);
	// }
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLine::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	// 1. Controllo validità
	if (!OtherActor || OtherActor == this) return;

	// 2. Controllo se è il Player
	if (ATheGauntletCharacter* PlayerChar = Cast<ATheGauntletCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Victory");
        
		if (ATheGauntletGameMode* GM = Cast<ATheGauntletGameMode>(GetWorld()->GetAuthGameMode()))
		{
			//CHIAMA LA FUNZIONE (Non il broadcast diretto)
			GM->TriggerLevelVictory();
		}
		
		
		// // 3. Fai partire il delegate o la logica
		// if (OnVictoryEvent.IsBound())
		// {
		// 	OnVictoryEvent.Broadcast();
		// }
	}
}
