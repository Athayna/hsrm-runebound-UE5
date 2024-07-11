#include "InventoryUI.h"

/**
 * @brief Function to construct the inventory UI
 * @details Sets the UI to update based on the game state and hides all item images and text by default
 */
void UInventoryUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Get the game state and set the UI to update based on the game state
    if (ARuneboundGameState* GS = Cast<ARuneboundGameState>(GetWorld()->GetGameState())) {
        UpdateInventoryUIFromMap(GS->GetInventory());
        GS->OnInventoryChanged.AddDynamic(this, &UInventoryUI::UpdateInventoryUIFromDelegate);
    }

    // Hide all item images and text by default
    InvisibilityImage->SetVisibility(ESlateVisibility::Hidden);
    FireballImage->SetVisibility(ESlateVisibility::Hidden);
    TelekinesisImage->SetVisibility(ESlateVisibility::Hidden);
    BerryImage->SetVisibility(ESlateVisibility::Hidden);
    BerryAmountText->SetVisibility(ESlateVisibility::Hidden);
    RunestoneImage->SetVisibility(ESlateVisibility::Hidden);
    RunestoneAmountText->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Function to update the inventory UI with a delegate
 * @details Calls the UpdateInventoryUIFromMap function with the inventory map from the delegate
 * 
 * @param Inventory The inventory map struct from the delegate
 */
void UInventoryUI::UpdateInventoryUIFromDelegate(FInventoryMap& Inventory)
{
    UpdateInventoryUIFromMap(Inventory.Map);
}

/**
 * @brief Function to update the inventory UI with a map
 * @details Shows the item images and text if they are in the inventory
 * 
 * @param Inventory The inventory map
 */
void UInventoryUI::UpdateInventoryUIFromMap(TMap<FString, int> Inventory)
{
    // Show the item images and text if they are in the inventory
    for (auto& Item : Inventory) {
        if (Item.Key == "Berry") {
            BerryImage->SetVisibility(ESlateVisibility::Visible);
            BerryAmountText->SetText(FText::FromString(FString::FromInt(Item.Value)));
            BerryAmountText->SetVisibility(ESlateVisibility::Visible);
        } else if (Item.Key == "RuneStone") {
            RunestoneImage->SetVisibility(ESlateVisibility::Visible);
            RunestoneAmountText->SetText(FText::FromString(FString::FromInt(Item.Value)));
            RunestoneAmountText->SetVisibility(ESlateVisibility::Visible);
        } else if (Item.Key == "InvisibilitySpell") {
            InvisibilityImage->SetVisibility(ESlateVisibility::Visible);
        } else if (Item.Key == "FireSpell") {
            FireballImage->SetVisibility(ESlateVisibility::Visible);
        } else if (Item.Key == "TelekinesisSpell") {
            TelekinesisImage->SetVisibility(ESlateVisibility::Visible);
        }
    }
}