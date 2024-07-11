#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "InteractablePrompt.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UInteractablePrompt : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;
	
private:
	/** Function to show the prompt UI */
	UFUNCTION(BlueprintCallable, Category = "Prompt")
	void ShowPrompt(AActor* OverlappedActor, AActor* OtherActor);

	/** Function to hide the prompt UI */
	UFUNCTION(BlueprintCallable, Category = "Prompt")
	void HidePrompt(AActor* OverlappedActor, AActor* OtherActor);

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Button image for the prompt */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> PromptButton;

	/** Text for the prompt */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> PromptText;
};
