#include "RuneboundGameState.h"
#include "QuestUI.h"
#include "InventoryUI.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Construct a new ARuneboundGameState::ARuneboundGameState object
 */
ARuneboundGameState::ARuneboundGameState()
{
    // Initialize the default inventory map
    Inventory.Map = TMap<FString, int>();
}

/**
 * @brief Called when the game starts or when spawned
 */
void ARuneboundGameState::BeginPlay()
{
    Super::BeginPlay();
}

/**
 * @brief Function to increment the count of an item in the inventory map by 1
 * 
 * @param ItemName The name of the item to add
 */
void ARuneboundGameState::AddToInventory(FString ItemName)
{
    // Add the item to the inventory map or increment the count if it already exists
    if (Inventory.Map.Contains(ItemName)) {
        Inventory.Map[ItemName] += 1;
    } else {
        Inventory.Map.Add(ItemName, 1);
    }

    // Print the inventory map to the log for debugging
    FString InventoryString = "Inventory: ";
    for (auto& Item : Inventory.Map) {
        InventoryString += Item.Key + ": " + FString::FromInt(Item.Value) + ", ";
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *InventoryString);

    // Broadcast the event to update the UI
    if (OnInventoryChanged.IsBound()) OnInventoryChanged.Broadcast(Inventory);
}

/**
 * @brief Function to remove an item from the inventory map
 * 
 * @param ItemName The name of the item to remove
 * @param Count The amount of the item to remove
 */
void ARuneboundGameState::RemoveFromInventory(FString ItemName, int Count)
{
    // Decrement the count of the item in the inventory map and remove it if the count is 0
    if (Inventory.Map.Contains(ItemName)) {
        Inventory.Map[ItemName] -= Count;
        
        // Removed to keep the item in the inventory map with a count of 0, so it still shows in the UI with a count of 0
        // if (Inventory.Map[ItemName] <= 0) {
        //     Inventory.Map.Remove(ItemName);
        // }
    }

    // Print the inventory map to the log for debugging
    FString InventoryString = "Inventory: ";
    for (auto& Item : Inventory.Map) {
        InventoryString += Item.Key + ": " + FString::FromInt(Item.Value) + ", ";
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *InventoryString);

    // Broadcast the event to update the UI
    if (OnInventoryChanged.IsBound()) OnInventoryChanged.Broadcast(Inventory);
}

/**
 * @brief Function to check if an item is in the inventory map
 * 
 * @param ItemName The name of the item to check for
 * @return True if the item is in the inventory map and false if it is not 
 */
bool ARuneboundGameState::CheckInventory(FString ItemName) const
{
    // Return true if the item is in the inventory map
    return Inventory.Map.Contains(ItemName);
}

/**
 * @brief Function to get the amount of an item in the inventory map
 * 
 * @param ItemName The name of the item to check for
 * @return Amount of item in inventory
 */
int ARuneboundGameState::GetInventoryCount(FString ItemName) const
{
    // Return the count of the item in the inventory map
    if (Inventory.Map.Contains(ItemName)) {
        return Inventory.Map[ItemName];
    } else {
        return 0;
    }
}

/**
 * @brief Getter for the inventory map
 * 
 * @return The inventory map
 */
TMap<FString, int> ARuneboundGameState::GetInventory() const
{
    return Inventory.Map;
}

/**
 * @brief Setter for the active quest
 * @details Sets the active quest and broadcasts the event
 * 
 * @param Quest The new active quest
 */
void ARuneboundGameState::SetActiveQuest(FString Quest)
{
    ActiveQuest = Quest;

    // Broadcast the event to update the UI
    if (OnActiveQuestChanged.IsBound()) OnActiveQuestChanged.Broadcast(ActiveQuest);
}

/**
 * @brief Getter for the active quest
 * 
 * @return The active quest
 */
FString ARuneboundGameState::GetActiveQuest() const
{
    return ActiveQuest;
}