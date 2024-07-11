#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CombinationChest.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "CombinationUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UCombinationUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Called when the game starts or when spawned */
	virtual void NativeConstruct() override;

private:
	/** Function to show the combination UI */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void ShowCombinationUI(AActor* InteractedActor);

	/** Function to hide the combination UI */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void HideCombinationUI();

	/** Function to increase the first number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void IncreaseNumber1();

	/** Function to decrease the first number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void DecreaseNumber1();

	/** Function to increase the second number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void IncreaseNumber2();

	/** Function to decrease the second number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void DecreaseNumber2();

	/** Function to increase the third number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void IncreaseNumber3();

	/** Function to decrease the third number */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void DecreaseNumber3();

	/** Function to submit the combination */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void SubmitCombination();

	/** Array with the number values */
	UPROPERTY(EditAnywhere, Category = "Combination")
	TArray<int32> NumberValues;

	/** Combination Chest reference */
	UPROPERTY(EditAnywhere, Category = "Combination")
	TObjectPtr<ACombinationChest> CombinationChest;

	/** Root widget for the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UImage> Background;

	/** Number on first wheel */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> Number1;

	/** Number on second wheel */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> Number2;

	/** Number on third wheel */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UTextBlock> Number3;

	/** Number1 increase button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number1Up;

	/** Number1 decrease button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number1Down;

	/** Number2 increase button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number2Up;

	/** Number2 decrease button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number2Down;

	/** Number3 increase button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number3Up;

	/** Number3 decrease button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> Number3Down;

	/** Submit button */
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI Elements")
	TObjectPtr<UButton> SubmitButton;
};
