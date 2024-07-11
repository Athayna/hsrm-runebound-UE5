#include "CombinationUI.h"

#include "Kismet/GameplayStatics.h"

/**
 * @brief Called when the game starts or when spawned
 */
void UCombinationUI::NativeConstruct()
{
    Super::NativeConstruct();

    RootWidget->SetVisibility(ESlateVisibility::Hidden);

    // Find the combination chest in the level and add a dynamic delegate to the OnInteracted event
    TArray<AActor*> CombinationChests = TArray<AActor*>();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACombinationChest::StaticClass(), CombinationChests);

    for (auto Actor : CombinationChests)
    {
        CombinationChest = Cast<ACombinationChest>(Actor);
        if (!CombinationChest) continue;
        CombinationChest->OnInteracted.AddDynamic(this, &UCombinationUI::ShowCombinationUI);
    }

    // Add dynamic delegates to the increase and decrease buttons, as well as the submit button
    Number1Up->OnClicked.AddDynamic(this, &UCombinationUI::IncreaseNumber1);
    Number1Down->OnClicked.AddDynamic(this, &UCombinationUI::DecreaseNumber1);
    Number2Up->OnClicked.AddDynamic(this, &UCombinationUI::IncreaseNumber2);
    Number2Down->OnClicked.AddDynamic(this, &UCombinationUI::DecreaseNumber2);
    Number3Up->OnClicked.AddDynamic(this, &UCombinationUI::IncreaseNumber3);
    Number3Down->OnClicked.AddDynamic(this, &UCombinationUI::DecreaseNumber3);
    SubmitButton->OnClicked.AddDynamic(this, &UCombinationUI::SubmitCombination);

    // Set the initial values of the numbers
    NumberValues.SetNum(3);
    NumberValues[0] = 0;
    NumberValues[1] = 0;
    NumberValues[2] = 0;

    // Set the text of the numbers
    Number1->SetText(FText::FromString(FString::FromInt(NumberValues[0])));
    Number2->SetText(FText::FromString(FString::FromInt(NumberValues[1])));
    Number3->SetText(FText::FromString(FString::FromInt(NumberValues[2])));
}

/**
 * @brief Function to show the combination UI
 */
void UCombinationUI::ShowCombinationUI(AActor* InteractedActor)
{
    // Show the combination UI
    RootWidget->SetVisibility(ESlateVisibility::Visible);

    // Set the focus to the first number
    Number1Up->SetKeyboardFocus();

    // Show mouse cursor and set input mode to UI only
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PlayerController->bShowMouseCursor = true;
        PlayerController->SetInputMode(FInputModeUIOnly());
    }
}

/**
 * @brief Function to hide the combination UI
 */
void UCombinationUI::HideCombinationUI()
{
    // Hide mouse cursor and set input mode to game only
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) 
    {
        PlayerController->bShowMouseCursor = false;
        PlayerController->SetInputMode(FInputModeGameOnly());
    }
    
    // Hide the combination UI
    RootWidget->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * @brief Function to increase the first number
 * @details Increase the value of NumberValues[0] by 1 and update the text
 */
void UCombinationUI::IncreaseNumber1()
{
    NumberValues[0] = (NumberValues[0] + 1) % 10;
    Number1->SetText(FText::FromString(FString::FromInt(NumberValues[0])));
}

/**
 * @brief Function to decrease the first number
 * @details Decrease the value of NumberValues[0] by 1 and update the text
 */
void UCombinationUI::DecreaseNumber1()
{
    NumberValues[0] = (NumberValues[0] - 1 + 10) % 10;
    Number1->SetText(FText::FromString(FString::FromInt(NumberValues[0])));
}

/**
 * @brief Function to increase the second number
 * @details Increase the value of NumberValues[1] by 1 and update the text
 */
void UCombinationUI::IncreaseNumber2()
{
    NumberValues[1] = (NumberValues[1] + 1) % 10;
    Number2->SetText(FText::FromString(FString::FromInt(NumberValues[1])));
}

/**
 * @brief Function to decrease the second number
 * @details Decrease the value of NumberValues[1] by 1 and update the text
 */
void UCombinationUI::DecreaseNumber2()
{
    NumberValues[1] = (NumberValues[1] - 1 + 10) % 10;
    Number2->SetText(FText::FromString(FString::FromInt(NumberValues[1])));
}

/**
 * @brief Function to increase the third number
 * @details Increase the value of NumberValues[2] by 1 and update the text
 */
void UCombinationUI::IncreaseNumber3()
{
    NumberValues[2] = (NumberValues[2] + 1) % 10;
    Number3->SetText(FText::FromString(FString::FromInt(NumberValues[2])));
}

/**
 * @brief Function to decrease the third number
 * @details Decrease the value of NumberValues[2] by 1 and update the text
 */
void UCombinationUI::DecreaseNumber3()
{
    NumberValues[2] = (NumberValues[2] - 1 + 10) % 10;
    Number3->SetText(FText::FromString(FString::FromInt(NumberValues[2])));
}

/**
 * @brief Function to submit the combination
 * @details Check if the combination is correct and call the Interact function of the combination chest
 */
void UCombinationUI::SubmitCombination()
{
    HideCombinationUI();                        // Hide the combination UI
    CombinationChest->CheckCode(NumberValues);  // Check the combination
}