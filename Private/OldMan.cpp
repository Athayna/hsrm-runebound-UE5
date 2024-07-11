#include "OldMan.h"

#include "Chest.h"

/**
 * @brief Construct a new AOldMan::AOldMan object
 * @details Set the dialogue lines for the conversation with the old man
 */
AOldMan::AOldMan()
{
    DialogueLines.Empty();
    DialogueLines.Add("I once was an adventurer like you. I hid one of those rune stones under a rock in the forest. Solve the riddle on my chest and I will give you the spell to move the rock.");
}

/**
 * @brief Called when the game starts or when spawned
 * @details Find the chest attached to the old man and hide it
 */
void AOldMan::BeginPlay()
{
    Super::BeginPlay();

    // Hide the old man
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    // Hide the chest
    TArray<AActor*> AttachedActors;
    GetAttachedActors(AttachedActors);
    for (AActor* Actor : AttachedActors)
    {
        if (AChest* ChestActor = Cast<AChest>(Actor))
        {
            Chest = ChestActor;
            Chest->SetActorHiddenInGame(true);
            Chest->SetActorEnableCollision(false);
            break;
        }
    }
}

/**
 * @brief Function to be called when the object is interacted with
 * @details On the first interaction, make the chest interactable and call the base class function
 */
void AOldMan::Interact()
{
    Super::Interact();
    if (Chest) Chest->SetActorEnableCollision(true);
}

/**
 * @brief Function to enable the chest and old man
 * @details Unhide the chest and old man
 */
void AOldMan::EnableOldMan()
{
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    if (Chest) Chest->SetActorHiddenInGame(false);
}
