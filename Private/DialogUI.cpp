#include "DialogUI.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"

/**
 * @brief Function to construct the dialog UI
 * @details This function constructs the dialog UI by setting the visibility of the UI elements to hidden and adding a dynamic delegate to the OnInteracted event for NPCs
 */
void UDialogUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Hide all UI elements by default
    CloseDialog();

    // Set values for the typewriter effect
    EndChars = {'.', '!', '?'};     // Default {'.', '!', '?'}
    PauseChars = {',', ';', ':'};   // Default {',', ';', ':'}
    TimeBetweenChars = 0.025f;      // Default 0.1f
    PauseAfterEndChar = 0.5f;       // Default 0.5f
    PauseAfterPauseChar = 0.25f;    // Default 0.25f

    // Get all interactable actors in the level and add a dynamic delegate to the OnInteracted event for NPCs
    TArray<AActor*> NPCs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC::StaticClass(), NPCs);

    for (auto Actor : NPCs) {
        ANPC* NPC = Cast<ANPC>(Actor);
        if (!NPC) continue;
        NPC->OnDialog.AddDynamic(this, &UDialogUI::UpdateDialogUI);
    }

    DialogButton->OnClicked.AddDynamic(this, &UDialogUI::StopTypeWriter);
    DialogButton->OnClicked.AddDynamic(this, &UDialogUI::CloseDialog);

    // Shows a start dialog when the game starts
    FString StartText = "Novice! Go find the 3 rune stones to activate the portal! Start your journey by going to the town! I know a fellow sorceress there who can help you!";
    UpdateDialogUI(StartText);
}

/**
 * @brief Function to update the dialog UI
 * @details This function updates the dialog UI by setting the Text to the Dialog and calling the StartTypeWriter function
 * 
 * @param Dialog The dialog to be displayed
 */
void UDialogUI::UpdateDialogUI(FString& Dialog)
{
    Text = FText::FromString(Dialog);
    StartTypeWriter();
}

/**
 * @brief Function to open the dialog UI
 * @details This function opens the dialog UI by setting the visibility of the UI elements to visible
 */
void UDialogUI::OpenDialog()
{
    // Show all UI elements
    RootWidget->SetVisibility(ESlateVisibility::Visible);

    // Show the mouse cursor for interaction
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PlayerController->bShowMouseCursor = true;
        PlayerController->SetInputMode(FInputModeUIOnly());
    }

    // Focus the dialog button
    DialogButton->SetKeyboardFocus();
}

/**
 * @brief Function to close the dialog UI
 * @details This function closes the dialog UI by setting the visibility of the UI elements to hidden
 */
void UDialogUI::CloseDialog()
{
    // Hide all UI elements
    RootWidget->SetVisibility(ESlateVisibility::Hidden);

    // Clear the dialog text
    DialogText->SetText(FText::FromString(""));

    // Hide the mouse cursor
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PlayerController->bShowMouseCursor = false;
        PlayerController->SetInputMode(FInputModeGameOnly());
    }
}

/**
 * @brief Function to start the typewriter effect
 * @details This function starts the typewriter effect by setting a timer to call the TypeText function
 */
void UDialogUI::StartTypeWriter()
{
    OpenDialog();
    ProcessedText = "";
    GetWorld()->GetTimerManager().SetTimer(TypeTextTimerHandle, this, &UDialogUI::TypeText, TimeBetweenChars, true);
}

/**
 * @brief Function to stop the typewriter effect
 * @details This function stops the typewriter effect by clearing the timer handle
 */
void UDialogUI::StopTypeWriter()
{
    GetWorld()->GetTimerManager().ClearTimer(TypeTextTimerHandle);  // Clear the timer handle
}

/**
 * @brief Function to type the text with a typewriter effect
 * @details This function types the text by adding a character to the ProcessedText string and setting the DialogText to the ProcessedText
 */
void UDialogUI::TypeText()
{
    if (Text.ToString().Len() > ProcessedText.Len())
    {
        ProcessedText += Text.ToString()[ProcessedText.Len()];
        DialogText->SetText(FText::FromString(ProcessedText));

        float Delay = TimeBetweenChars;
        if (EndChars.Contains(ProcessedText[ProcessedText.Len() - 1]))
        {
            Delay = PauseAfterEndChar;
        }
        else if (PauseChars.Contains(ProcessedText[ProcessedText.Len() - 1]))
        {
            Delay = PauseAfterPauseChar;
        }

        GetWorld()->GetTimerManager().SetTimer(TypeTextTimerHandle, this, &UDialogUI::TypeText, Delay, false);
    }
    else
    {
        StopTypeWriter();
    }
}

