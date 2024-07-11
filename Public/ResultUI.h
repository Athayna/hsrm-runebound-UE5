#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "ResultUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UResultUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;
	
private:
	/* Function to handle the back button click */
	UFUNCTION()
	void BackToTitle();

	/* Function to handle the quit button click */
	UFUNCTION()
	void QuitGame();

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the result screen */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> ResultBackground;

	/** Back to Title button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> BackToTitleButton;

	/** Quit button to close the game */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> QuitButton;
};
