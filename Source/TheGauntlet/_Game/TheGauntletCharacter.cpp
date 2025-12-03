// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGauntletCharacter.h"

#include <string>

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TheGauntlet.h"
#include "Interactable.h"
#include "HealthComponent.h"
#include "TheGauntletGameMode.h"
#include "Engine/OverlapResult.h"

ATheGauntletCharacter::ATheGauntletCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnDeath.AddDynamic(this, &ATheGauntletCharacter::DoOnDeath);
}

void ATheGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheGauntletCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATheGauntletCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheGauntletCharacter::Look);
	}
	else
	{
		UE_LOG(LogTheGauntlet, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheGauntletCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ATheGauntletCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATheGauntletCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ATheGauntletCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATheGauntletCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ATheGauntletCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ATheGauntletCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Interacting");
	
	TArray<FOverlapResult> list = TryInteract();

	for (const FOverlapResult& Result : list)
	{
		// Result.GetActor() restituisce l'attore coinvolto
		AActor* OverlappedActor = Result.GetActor();

		if (OverlappedActor && OverlappedActor->Implements<UInteractable>()) 
		{
			IInteractable::Execute_Interact(OverlappedActor, this);
			break;
		}
	}
}

void ATheGauntletCharacter::Punch()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Damaging");

	TArray<FOverlapResult> list = TryInteract();

	for (const FOverlapResult& Result : list)
	{
		// Result.GetActor() restituisce l'attore coinvolto
		AActor* OverlappedActor = Result.GetActor();

		if (OverlappedActor) 
		{
			UHealthComponent* TargetHealthComp = OverlappedActor->FindComponentByClass<UHealthComponent>();

			if (TargetHealthComp)
			{
				// Se esiste, chiamiamo la funzione pubblica del componente
				TargetHealthComp->HandleTakeDamage(damage);
				break; 
			}
		}
	}
}

TArray<FOverlapResult> ATheGauntletCharacter::TryInteract()
{
	FVector StartLocation = GetActorLocation();
    
	// Creiamo la forma della sfera
	FCollisionShape MySphere = FCollisionShape::MakeSphere(interactionRange);

	// Array per contenere tutti i risultati (non esiste OverlapSingleByChannel)
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignora il player

	// Eseguiamo l'Overlap
	// Restituisce true se ha trovato qualcosa
	bool bHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		StartLocation,
		FQuat::Identity, // Nessuna rotazione
		ECC_Visibility,  // Canale Visibility
		MySphere,
		QueryParams
	);

	// DEBUG VISIVO
	DrawDebugSphere(GetWorld(), StartLocation, interactionRange, 12, bHit ? FColor::Green : FColor::Red, false, 2.0f);

	// FHitResult "finto" da restituire (per mantenere compatibilità col tuo codice esistente)
	return OverlapResults;
}

void ATheGauntletCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Landed");
	
	float FallingSpeed = -GetVelocity().Z; 
	

	//3. Verifica se abbiamo superato la soglia di sicurezza
	if (FallingSpeed > minFallVelocity)
	{
		// 4. Calcolo del danno
		// Esempio: (1500 - 1000) * 0.05 = 25 Danno
		float ExcessSpeed = FallingSpeed - minFallVelocity;
		float DamageToApply = ExcessSpeed * fallDmgMultiplier;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, std::to_string(DamageToApply).c_str());
		HealthComp->HandleTakeDamage(DamageToApply);
	}
}

void ATheGauntletCharacter::DoOnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, "Dead Actor");
	
	if (ATheGauntletGameMode* GM = Cast<ATheGauntletGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//CHIAMA LA FUNZIONE (Non il broadcast diretto)
		GM->TriggerLost();
	}
}

