#include "Rock.h"

#include "RuneboundGameState.h"

/**
 * @brief Construct a new ARock::ARock object
 * @details Set the collectable flag to false and the unique interaction flag to true
 */
ARock::ARock()
{
    bCollectable = false;  // Rocks are not collectable
    bUniqueInteraction = true;  // Rocks can only be interacted with once
}

/**
 * @brief Called when the game starts or when spawned
 */
void ARock::BeginPlay()
{
    Super::BeginPlay();

    // Turn off collision for the sphere collider
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

/**
 * @brief Function to be called when the object is interacted with
 */
void ARock::Interact()
{
    if (ARuneboundGameState* GS = GetWorld()->GetGameState<ARuneboundGameState>())
    {
        if (GS->CheckInventory("TelekinesisSpell"))  // Check if the player has the TelekinesisSpell in their inventory
        {
            Super::Interact();  // Call the parent class's Interact function
            // Moves via timeline animation in the Blueprint version
            //  SetActorLocation(FVector(2380.0f, 9850.0f, 0.0f)); // Move the rock to a new location
            //  Stop audio after 2.5 seconds (animation length in the Blueprint version)
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { Audio->Stop(); }, 2.5f, false);
        }
    }
}

/**
 * @brief Function enabling the rock to be interacted with
 * @details Enable the sphere collider, making the rock interactable
 */
void ARock::EnableRock()
{
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
