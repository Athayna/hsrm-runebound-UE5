#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "PauseUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UPauseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Destructor */
	virtual ~UPauseUI() = default;

protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;
	
private:
	/** Function to handle the pause event */
	UFUNCTION()
	void HandlePause();

	/** Function to open the pause menu */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void OpenPauseMenu();

	/** Function to close the pause menu */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void ClosePauseMenu();

	/** Function to open the controls */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void OpenControls();

	/** Function to close the controls */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void CloseControls();

	/** Function to handle the continue button click */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void Continue();

	/** Function to handle the back to title button click */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void BackToTitle();

	/** Function to handle the quit button click */
	UFUNCTION(BlueprintCallable, Category = "PauseMenu")
	void Quit();

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> PauseBackground;

	/** Continue button for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> ContinueButton;

	/** Controls button for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> ControlsButton;

	/** Back to Title button for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> BackToTitleButton;

	/** Quit button for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> QuitButton;

	/** Controls image for the pause menu */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> ControlsImage;

	/** Back button for the controls */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> ControlsBackButton;
};