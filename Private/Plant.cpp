#include "Plant.h"
#include "RuneboundGameState.h"
#include "Particles/ParticleSystemComponent.h"

/**
 * @brief Construct a new APlant::APlant object
 */
APlant::APlant()
{
    bCollectable = false;       // The giant plant is not collectable
    bUniqueInteraction = true;  // The giant plant can only be burned once

    Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));  // Create the fire particle system
    Fire->SetupAttachment(StaticMesh);                                      // Attach the fire particle system to the static mesh
    Fire->SetVisibility(false);                                             // Hide the fire particle system

    // Turn off collision for the sphere collider
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

/**
 * @brief Called when the game starts or when spawned
 */
void APlant::BeginPlay()
{
    Super::BeginPlay();
}

/**
 * @brief Function to be called when the object is interacted with
 */
void APlant::Interact()
{
    if (ARuneboundGameState* GS = GetWorld()->GetGameState<ARuneboundGameState>())
    {
        if (GS->CheckInventory("FireSpell"))  // Check if the player has the FireSpell in their inventory
        {
            Super::Interact();  // Call the parent class's Interact function
            Fire->SetVisibility(true);  // Show the fire particle system
            // Destroy the plant after 4 seconds
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { Destroy(); }, 4.0f, false);
        }
    }
}

/**
 * @brief Function to enable the plant
 * @details Enable the sphere collider, making the plant interactable
 */
void APlant::EnablePlant()
{
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}