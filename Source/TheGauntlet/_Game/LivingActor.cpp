// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/LivingActor.h"

#include <string>

#include "HealthComponent.h"

// Sets default values
ALivingActor::ALivingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnDeath.AddDynamic(this, &ALivingActor::DoOnDeath);
	
	HealthComp->OnDamage.AddDynamic(this, &ALivingActor::UpdateColorBasedOnHealth);
}

// Called when the game starts or when spawned
void ALivingActor::BeginPlay()
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
void ALivingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALivingActor::DoOnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Dead Actor");
	Destroy();
}

void ALivingActor::UpdateColorBasedOnHealth()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "damage delegate override");
	
	if (!DynamicMat) return;

	// Calcolo percentuale (0.0 - 1.0)
	float HealthPercent = FMath::Clamp(HealthComp->CurrentHealth / HealthComp->MaxHealth, 0.0f, 1.0f);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, std::to_string(HealthPercent).c_str());
	// Calcolo colore scuro
	FLinearColor DarkerColor = InitialColor * HealthPercent;

	// Applica
	DynamicMat->SetVectorParameterValue(FName("ColorParam"), DarkerColor);
}

