#include "RuneboundGameMode.h"
#include "RuneboundCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "RuneboundGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Interactable.h"
#include "EnhancedInputComponent.h"
#include "PauseUI.h"
#include "GameFramework/HUD.h"
#include "Portal.h"
#include "OldMan.h"
#include "Rock.h"
#include "Plant.h"

/**
 * @brief Constructor for ARuneboundGameMode
 * @details Sets the default pawn class to BP_ThirdPersonCharacter and the default Game State class to ARuneboundGameState
 */
ARuneboundGameMode::ARuneboundGameMode()
{
	// Set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // Set the default Game State class to ARuneboundGameState
    GameStateClass = ARuneboundGameState::StaticClass();

    // Fill the array of quests in the order they should be completed
    Quests.Add("Head to the town and find clues about the rune stones");            // At the start of the game
    Quests.Add("Collect 5 berries for the sorceress's potion");                     // OnInteracted("Mage")
    Quests.Add("Use the spell to traverse the miasma and find the first rune stone");// GetInventoryCount("InvisibilitySpell") == 1
    Quests.Add("Find the giant plant hiding the rune stone in the forest");         // GetInventoryCount("FireSpell") == 1 && GetInventoryCount("RuneStone") == 1
    Quests.Add("The adventurer seems to be back in the town, maybe he knows more"); // GetInventoryCount("RuneStone") == 2
    Quests.Add("Find the combination for the old man's chest");                     // OnInteracted("OldMan")
    Quests.Add("Find the big rock hiding the rune stone in the forest");            // OnItemAdded("TelekinesisSpell", 1)
    Quests.Add("Return to the portal and place the rune stones");                   // GetInventoryCount("RuneStone") == 3
    Quests.Add("Step through the portal...");                                       // OnInteracted("Portal")

    // Set the references to the Interactables to nullptr to set them in BeginPlay
    Portal = nullptr;
    OldMan = nullptr;
    Rock = nullptr;
    Plant = nullptr;
}

/**
 * @brief Called when the game starts or when spawned
 * @details Gets all actors of the Interactable class and adds a dynamic delegate to the OnDestroyed event and OnInteracted event
 */
void ARuneboundGameMode::BeginPlay()
{
    Super::BeginPlay();

    GetGameState<ARuneboundGameState>()->SetActiveQuest(Quests[0]);             // Set the active quest to the first quest

    TArray<AActor*> Interactables;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractable::StaticClass(), Interactables);     // Get all actors of the Interactable class
    
    // Loop through all actors and add a dynamic delegate to the OnDestroyed event
    for (auto Actor : Interactables)
    {
        AInteractable* Interactable = Cast<AInteractable>(Actor);
        if (!Interactable) continue;  // Skip to the next actor if the current actor is not an AInteractable (should never happen, but just in case)

        if(!Portal) Portal = Cast<APortal>(Interactable);  // Set the Portal reference if it is not already set
        if(!OldMan) OldMan = Cast<AOldMan>(Interactable);  // Set the OldMan reference if it is not already set
        if(!Rock) Rock = Cast<ARock>(Interactable);        // Set the Rock reference if it is not already set
        if(!Plant) Plant = Cast<APlant>(Interactable);     // Set the Plant reference if it is not already set

        if (Interactable->GetCollectable()) {
            Interactable->OnDestroyed.AddDynamic(this, &ARuneboundGameMode::OnCollectableDestroyed);
        }
        else {
            Interactable->OnInteracted.AddDynamic(this, &ARuneboundGameMode::OnInteracted);
        }
    }
}

/**
 * @brief Function that adds the collectable to the inventory when it is destroyed and updates the active quest
 * @details Gets the name of the collectable's class and removes the "BP_" prefix and "_C" suffix. Then adds the collectable to the inventory using the instance of ARuneboundGameState
 * 
 * @param Collectable The collectable that was destroyed
 */
void ARuneboundGameMode::OnCollectableDestroyed(AActor* Collectable)
{
    FString Name = Collectable->GetClass()->GetName();  // Get the name of the collectable's class
    Name.RemoveFromStart("BP_");                        // Remove the "BP_" prefix from the name
    Name.RemoveFromEnd("_C");                           // Remove the "_C" suffix from the name

    ARuneboundGameState *GS = GetGameState<ARuneboundGameState>();  // Get the instance of ARuneboundGameState

    GS->AddToInventory(Name);  // Add the collectable to the inventory using the instance of ARuneboundGameState

    // Check if any of the quests are completed
    if (Name == "InvisibilitySpell") GS->SetActiveQuest(Quests[2]);
    else if ((Name == "FireSpell" || Name == "RuneStone") && GS->GetInventoryCount("RuneStone") == 1 && GS->GetInventoryCount("FireSpell") == 1)
    {
        GS->SetActiveQuest(Quests[3]);
        if (Plant) Plant->EnablePlant(); // Enable the plant, making it interactable
    }
    else if (Name == "RuneStone" && GS->GetInventoryCount("RuneStone") == 2) {
        GS->SetActiveQuest(Quests[4]);
        if (OldMan) OldMan->EnableOldMan(); // Enable the OldMan, making it interactable
    }
    else if (Name == "TelekinesisSpell")
    {
        GS->SetActiveQuest(Quests[6]);
        if (Rock) Rock->EnableRock(); // Enable the rock, making it interactable
    }
    else if (Name == "RuneStone" && GS->GetInventoryCount("RuneStone") == 3)
    {
        GS->SetActiveQuest(Quests[7]);
        if (Portal) Portal->EnablePortal(); // Enable the portal, making it interactable
    }
    
    // Log quest if changed for debugging purposes
    else return;
    UE_LOG(LogTemp, Warning, TEXT("Quest: %s"), *GS->GetActiveQuest());
}

/**
 * @brief Function that updates the active quest depending on which interactable was interacted with
 * @details Gets the name of the interactable's class and removes the "BP_" prefix and "_C" suffix. Then updates the active quest depending on the name of the interactable
 * 
 * @param Actor The actor that was interacted with
 */
void ARuneboundGameMode::OnInteracted(AActor* Actor)
{
    AInteractable *Interactable = Cast<AInteractable>(Actor);
    if(!Interactable) return;
    FString Name = Interactable->GetClass()->GetName(); // Get the name of the interactable's class
    Name.RemoveFromStart("BP_");                        // Remove the "BP_" prefix from the name
    Name.RemoveFromEnd("_C");                           // Remove the "_C" suffix from the name

    ARuneboundGameState *GS = GetGameState<ARuneboundGameState>();  // Get the instance of ARuneboundGameState

    // Check if any of the quests are completed
    if (Name == "Mage") GS->SetActiveQuest(Quests[1]);
    else if (Name == "OldMan") GS->SetActiveQuest(Quests[5]);
    else if (Name == "Portal") GS->SetActiveQuest(Quests[8]);

    // Log quest if changed for debugging purposes
    else return;
    UE_LOG(LogTemp, Warning, TEXT("Quest: %s"), *GS->GetActiveQuest());
}