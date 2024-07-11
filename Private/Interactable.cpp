#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	
	SetRootComponent(SceneRoot);
	Audio->SetupAttachment(SceneRoot);
	StaticMesh->SetupAttachment(SceneRoot);
	SphereCollider->SetupAttachment(StaticMesh);

	Audio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	Audio->Stop(); // Stop the audio component from playing on begin play
}

/**
 * @brief Function to be called when the object is interacted with. Destroys the object if it is collectable.
 * 
 */
void AInteractable::Interact()
{
	// Play the sound if it exists
	if (Audio->Sound) Audio->Play();

	// Destroy the object if it is collectable or remove the collision if it is a unique interaction
	if (bCollectable) {
		if (Audio->Sound) {
			this->SetActorHiddenInGame(true);		// Hide the object
			this->SetActorEnableCollision(false);	// Disable collision
			FTimerHandle TimerHandle;				// Create a timer handle
			FTimerDelegate TimerDelegate;			// Create a timer delegate
			TimerDelegate.BindLambda([this](){		// Bind the timer delegate to a lambda function that destroys the object
				Destroy();
			});
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Audio->Sound->Duration, false);	// Set the timer to destroy the object after the sound duration
		} else {
			Destroy();
		}
		UE_LOG(LogTemp, Warning, TEXT("Destroyed %s"), *GetName());
	}
	else if (bUniqueInteraction) {
		// Remove overlapping collision from the interactable
		SphereCollider->UnregisterComponent();
		SphereCollider->DestroyComponent();
		
		// Log removal of collision
		UE_LOG(LogTemp, Warning, TEXT("Removed collision from %s"), *GetName());
	}

	// Broadcast the interaction event
	if (OnInteracted.IsBound()) OnInteracted.Broadcast(this);
}

/**
 * @brief Getter for bUniqueInteraction
 * 
 * @return True if the object is only interactable once and false if it is not
 */
bool AInteractable::GetUniqueInteraction()
{
	return bUniqueInteraction;
}

/**
 * @brief Getter for bCollectable
 * 
 * @return True if the object is collectable and false if it is not
 */
bool AInteractable::GetCollectable()
{
	return bCollectable;
}