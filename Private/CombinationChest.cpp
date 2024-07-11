#include "CombinationChest.h"

#include "Kismet/GameplayStatics.h"

/**
 * @brief Constructor
 */
ACombinationChest::ACombinationChest()
{
    // Set the combination code
    CombinationCode.SetNum(3);
    CombinationCode[0] = 3;
    CombinationCode[1] = 4;
    CombinationCode[2] = 6;
}

/**
 * @brief Called when the game starts or when spawned
 */
void ACombinationChest::BeginPlay()
{
    Super::BeginPlay();
}

/**
 * @brief Function to be called when the object is interacted with
 */
void ACombinationChest::Interact()
{
    if (OnInteracted.IsBound()) OnInteracted.Broadcast(this);    // Broadcast the interaction event
}

void ACombinationChest::CheckCode(TArray<int32> Code)
{
    // Check if the code is correct
    if (Code[0] == CombinationCode[0] && Code[1] == CombinationCode[1] && Code[2] == CombinationCode[2])
    {
        if (OnInteracted.IsBound()) OnInteracted.Clear();           // Clear the interaction event binding so the UI does not show again
        OnCorrectCode.Broadcast();                                  // Broadcast the correct code event to play the animation
        Super::Interact();                                          // Call the parent interact function to open the chest and play the sound
    }
    else
    {
        // Play a sound to indicate the code is incorrect
        if (IncorrectCodeSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), IncorrectCodeSound, GetActorLocation());
    }
}