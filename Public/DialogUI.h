#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "TimerManager.h"

#include "DialogUI.generated.h"

/**
 * @brief A user interface for displaying dialog
 */
UCLASS()
class RUNEBOUND_API UDialogUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;

private:
	/** Function to update the dialog UI */
	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void UpdateDialogUI(FString& Dialog);

	/** Function to close the dialog */
	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void CloseDialog();

	/** Function to open the dialog */
	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void OpenDialog();

	/** Array of characters that signal the end of a sentence */
    TArray<TCHAR> EndChars;

	/** Array of characters that signal a pause in a sentence */
    TArray<TCHAR> PauseChars;

	/** Time between characters during the typewriter effect */
    UPROPERTY(EditAnywhere, Category = "TypeWriterEffect")
    float TimeBetweenChars;

	/** Time to pause after an end character */
    UPROPERTY(EditAnywhere, Category = "TypeWriterEffect")
    float PauseAfterEndChar;

	/** Time to pause after a pause character */
    UPROPERTY(EditAnywhere, Category = "TypeWriterEffect")
    float PauseAfterPauseChar;

	/** Function to start the typewriter effect */
	UFUNCTION(BlueprintCallable, Category = "TypeWriterEffect")
    void StartTypeWriter();

	/** Function to stop the typewriter effect */
	UFUNCTION(BlueprintCallable, Category = "TypeWriterEffect")
	void StopTypeWriter();

	/** Function to type the text with a typewriter effect */
	UFUNCTION(BlueprintCallable, Category = "TypeWriterEffect")
	void TypeText();

	/** Text to display in the dialog */
	UPROPERTY(VisibleAnywhere, Category = "TypeWriterEffect")
	FText Text;

	/** Processed text for the typewriter effect */
	UPROPERTY(VisibleAnywhere, Category = "TypeWriterEffect")
	FString ProcessedText;

	/** Timer handle for the typewriter effect */
	UPROPERTY(VisibleAnywhere, Category = "TypeWriterEffect")
    FTimerHandle TypeTextTimerHandle;

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the dialog */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> DialogBackground;

	/** Text for the dialog */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> DialogText;

	/** Image for the button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> DialogButtonImage;

	/** Text for the button prompt */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> DialogButtonText;

	/** Button to close the dialog */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> DialogButton;
};
