#include "Mage.h"

#include "Chest.h"
#include "RuneboundGameState.h"

/**
 * @brief Construct a new AMage::AMage object
 */
AMage::AMage()
{
    // Set the dialogue lines for the mage
    DialogueLines.Empty();

    DialogueLines.Add("I am a friend of your master. I can teach you a spell to savely traverse the miasma if you bring me five berries from the forest.");
    DialogueLines.Add("I have been studying the miasma for years. I can teach you a spell to safely traverse it if you bring me five berries for my potion.");
}

/**
 * @brief Called when the game starts or when spawned
 */
void AMage::BeginPlay()
{
    Super::BeginPlay();

    // Find the chest attached to the mage
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
 * @details If the player has the berries, replace the dialogue with the final dialogue and unhide the treasure
 */
void AMage::Interact()
{
    // If the player has the berries, replace the dialogue with the final dialogue and unhide the treasure
    if (ARuneboundGameState* GS = Cast<ARuneboundGameState>(GetWorld()->GetGameState())) {
        if (GS->GetInventoryCount("Berry") >= 5) {
            GS->RemoveFromInventory("Berry", 5);
            DialogueLines.Empty(); // Clear the dialogue lines so the final dialogue is the only one displayed when the player interacts with the mage again
            DialogueLines.Add("You have brought me the berries I need. The chest next to me contains the spell you seek. Good luck on your journey.");
            if (Chest) {
                Chest->SetActorHiddenInGame(false);
                Chest->SetActorEnableCollision(true);
            }
        }
    }

    // Call the base class function
    Super::Interact();
}