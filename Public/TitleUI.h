#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Destructor */
	virtual ~UTitleUI() = default;

protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;
	
private:
	/* Function to handle the start button click */
	UFUNCTION()
	void StartGame();

	/* Function to handle the controls button click */
	UFUNCTION()
	void OpenControls();

	/* Function to handle the back button click */
	UFUNCTION()
	void CloseControls();

	/* Function to handle the quit button click */
	UFUNCTION()
	void QuitGame();

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the title screen */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> TitleBackground;

	/** Start button to start the game */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> StartButton;

	/** Controls button to open the controls panel */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> ControlsButton;

	/** Controls panel to display the controls */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> ControlsBackground;

	/** Back button to close the controls panel */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> ControlsBackButton;

	/** Quit button to close the game */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> QuitButton;
};
