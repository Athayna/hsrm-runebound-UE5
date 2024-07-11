
#include "Chest.h"

/**
 * @brief Construct a new AChest::AChest object
 * @details Set the collectable flag to false and the unique interaction flag to true
 */
AChest::AChest()
{
    bCollectable = false;                                                       // Chests are not collectable
    bUniqueInteraction = true;                                                  // Chests can only be opened with once

    ChestTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestTop"));  // Create the chest top
    ChestTop->SetupAttachment(StaticMesh);                                      // Attach the chest top to the static mesh

    Loot = TArray<AActor*>();                                                   // Initialize the loot array
}

/**
 * @brief Called when the game starts or when spawned
 */
void AChest::BeginPlay()
{
    Super::BeginPlay();

    GetAttachedActors(Loot);    // Get all attached actors and add them to the loot array

    // Disable collision and hide the loot
    for (AActor* Item : Loot)
    {
        if (!Item) continue;
        Item->SetActorHiddenInGame(true);
        Item->SetActorEnableCollision(false);
    }
}

/**
 * @brief Function to be called when the object is interacted with
 */
void AChest::Interact()
{
    Super::Interact();

    OpenChest();    // Open the chest
}

/**
 * @brief Opens the chest
 * @details Rotates the chest top and shows the loot inside
 */
void AChest::OpenChest()
{
    // Rotate the chest top 70 degrees (replaced with Timeline animation in the Blueprint version)
    // FRotator NewRotation = ChestTop->GetComponentRotation();
    // NewRotation.Roll += 70.0f;
    // ChestTop->SetWorldRotation(NewRotation);

    // Enable collision and show the loot
    for (AActor* Item : Loot)
    {
        if (!Item) continue;
        Item->SetActorHiddenInGame(false);
        Item->SetActorEnableCollision(true);
    }
}