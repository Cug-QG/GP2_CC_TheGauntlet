// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Lever.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
	TargetMesh = FindComponentByClass<UStaticMeshComponent>();
	
	if (TargetMesh)
	{
		// 2. Creiamo il materiale dinamico sulla mesh trovata (Slot 0)
		DynamicMat = TargetMesh->CreateAndSetMaterialInstanceDynamic(0);

		if (DynamicMat)
		{
			// 3. Salviamo il colore di partenza
			DynamicMat->GetVectorParameterValue(FName("ColorParam"), InitialColor);
            
			UE_LOG(LogTemp, Log, TEXT("Mesh trovata e Materiale Dinamico creato!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ATTENZIONE: Nessuna Static Mesh trovata in questo Blueprint!"));
	}
	
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALever::Interact_Implementation(ATheGauntletCharacter* interacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Being Interacted");

	ITGOrderReceiver::Execute_DoOrder(linkedObject.GetObject(), this);
	DynamicMat->SetVectorParameterValue(FName("ColorParam"), FLinearColor::Black);

	// 2. AVVIA IL TIMER (Durata 0.1 secondi)
	// Se prendi tanti colpi di fila, SetTimer resetta il conteggio, 
	// quindi rimani bianco finché smettono di colpirti. Perfetto.
	GetWorld()->GetTimerManager().SetTimer(
		FlashTimerHandle, 
		this, 
		&ALever::OnFlashEnded, 
		0.1f, // Durata del flash
		false // Non deve ripetersi in loop
	);
}

void ALever::OnFlashEnded()
{
	DynamicMat->SetVectorParameterValue(FName("ColorParam"), InitialColor);
}

