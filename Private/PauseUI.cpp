#include "PauseUI.h"

#include "Kismet/GameplayStatics.h"
#include <Runebound/RuneboundCharacter.h>

/**
 * @brief Function to construct the pause UI
 * @details This function constructs the pause UI by setting the visibility of the UI elements to hidden and binding the pause action
 */
void UPauseUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Hide all UI elements by default
    RootWidget->SetVisibility(ESlateVisibility::Hidden);
    ControlsImage->SetVisibility(ESlateVisibility::Hidden);
    ControlsBackButton->SetVisibility(ESlateVisibility::Hidden);

    // Bind the character's pause action to the HandlePause function
    if (ARuneboundCharacter* Character = Cast<ARuneboundCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())) {
        Character->OnPause.AddDynamic(this, &UPauseUI::HandlePause);
    }

    // Bind the buttons to their respective functions
    ContinueButton->OnClicked.AddDynamic(this, &UPauseUI::Continue);
    ControlsButton->OnClicked.AddDynamic(this, &UPauseUI::OpenControls);
    ControlsBackButton->OnClicked.AddDynamic(this, &UPauseUI::CloseControls);
    BackToTitleButton->OnClicked.AddDynamic(this, &UPauseUI::BackToTitle);
    QuitButton->OnClicked.AddDynamic(this, &UPauseUI::Quit);
}

/**
 * @brief Function to handle the pause event
 * @details This function handles the pause event by checking if the game is paused and opening or closing the pause menu accordingly
 */
void UPauseUI::HandlePause()
{
    if (UGameplayStatics::IsGamePaused(GetWorld())) OpenPauseMenu();
    else ClosePauseMenu();
}

/**
 * @brief Function to open the pause menu
 * @details This function opens the pause menu by showing all UI elements
 */
void UPauseUI::OpenPauseMenu()
{
    // Focus the continue button
    ContinueButton->SetKeyboardFocus();

    // Show all Pause UI elements
    RootWidget->SetVisibility(ESlateVisibility::Visible);
}

/**
 * @brief Function to close the pause menu
 * @details This function closes the pause menu by hiding all UI elements and unpausing the game
 */
void UPauseUI::ClosePauseMenu()
{
    // Hide all UI elements
    RootWidget->SetVisibility(ESlateVisibility::Hidden);
    CloseControls();
}

/**
 * @brief Function to open the controls
 * @details This function opens the controls UI elements by showing the ControlsImage and ControlsBackButton and closing the pause menu
 */
void UPauseUI::OpenControls()
{
    // Show the controls UI elements
    ControlsImage->SetVisibility(ESlateVisibility::Visible);
    ControlsBackButton->SetVisibility(ESlateVisibility::Visible);

    // Focus the back button
    ControlsBackButton->SetKeyboardFocus();
}

/**
 * @brief Function to close the controls
 * @details This function closes the controls UI elements by hiding the ControlsImage and ControlsBackButton and opening the pause menu
 */
void UPauseUI::CloseControls()
{
    // Hide the controls UI elements
    ControlsImage->SetVisibility(ESlateVisibility::Hidden);
    ControlsBackButton->SetVisibility(ESlateVisibility::Hidden);

    // Focus the continue button
    ContinueButton->SetKeyboardFocus();
}

void UPauseUI::Continue()
{
    // Close the pause menu
    ClosePauseMenu();

    // Unpause the game
    // TODO: This should be done in the character class
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPauseUI::BackToTitle()
{
    // Return to the title screen
    UGameplayStatics::OpenLevel(GetWorld(), "Title");
}

void UPauseUI::Quit()
{
    // Quit the game
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
