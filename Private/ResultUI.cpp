#include "ResultUI.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Function to construct the result UI
 * @details This function constructs the result UI by binding the button click events
 */
void UResultUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the button click events
    BackToTitleButton->OnClicked.AddDynamic(this, &UResultUI::BackToTitle);
    QuitButton->OnClicked.AddDynamic(this, &UResultUI::QuitGame);

    // Set the focus to the back to title button
    BackToTitleButton->SetKeyboardFocus();
}

/**
 * @brief Function to handle the back button click
 * @details This function handles the back button click by opening the title screen
 */
void UResultUI::BackToTitle()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Title");
}

/**
 * @brief Function to handle the quit button click
 * @details This function handles the quit button click by quitting the game
 */
void UResultUI::QuitGame()
{
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}