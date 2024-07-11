#include "TitleUI.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Function to construct the title UI
 * @details This function constructs the title UI by setting the visibility of the UI elements to hidden and binding the button click events
 */
void UTitleUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Hide the controls panel by default
    ControlsBackground->SetVisibility(ESlateVisibility::Hidden);
    ControlsBackButton->SetVisibility(ESlateVisibility::Hidden);

    // Bind the button click events
    StartButton->OnClicked.AddDynamic(this, &UTitleUI::StartGame);
    ControlsButton->OnClicked.AddDynamic(this, &UTitleUI::OpenControls);
    ControlsBackButton->OnClicked.AddDynamic(this, &UTitleUI::CloseControls);
    QuitButton->OnClicked.AddDynamic(this, &UTitleUI::QuitGame);

    // Set the focus to the start button
    StartButton->SetKeyboardFocus();
}

/**
 * @brief Function to handle the start button click
 * @details This function handles the start button click by starting the game
 */
void UTitleUI::StartGame()
{
    // Start the game by opening the level
    UGameplayStatics::OpenLevel(GetWorld(), "Main");
}

/**
 * @brief Function to handle the controls button click
 * @details This function handles the controls button click by opening the controls panel and focusing the back button
 */
void UTitleUI::OpenControls()
{
    // Show the controls panel
    ControlsBackground->SetVisibility(ESlateVisibility::Visible);
    ControlsBackButton->SetVisibility(ESlateVisibility::Visible);

    // Focus the back button
    ControlsBackButton->SetKeyboardFocus();
}

/**
 * @brief Function to handle the back button click
 * @details This function handles the back button click by closing the controls panel and focusing the start button
 */
void UTitleUI::CloseControls()
{
    // Hide the controls panel
    ControlsBackground->SetVisibility(ESlateVisibility::Hidden);
    ControlsBackButton->SetVisibility(ESlateVisibility::Hidden);

    // Focus the start button
    StartButton->SetKeyboardFocus();
}

/**
 * @brief Function to handle the quit button click
 * @details This function handles the quit button click by quitting the game
 */
void UTitleUI::QuitGame()
{
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
