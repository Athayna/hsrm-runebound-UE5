#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "RuneboundGameState.h"

#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	/** Function to update the active quest UI with a delegate */
	UFUNCTION(Category = "Event")
	void UpdateInventoryUIFromDelegate(FInventoryMap& Inventory);

	/** Function to update the active quest UI with a map */
	UFUNCTION(Category = "Update")
	void UpdateInventoryUIFromMap(TMap<FString, int> Inventory);

	/** Root widget of the UI */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UPanelWidget> RootWidget;

	/** Background image for the inventory */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> InventoryBar;

	/** Invisibility image */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> InvisibilityImage;
	
	/** Fireball image */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> FireballImage;

	/** Telekinesis image */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> TelekinesisImage;

	/** Berry image */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> BerryImage;

	/** Berry amount text */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> BerryAmountText;

	/** Runestone image */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> RunestoneImage;

	/** Runestone amount text */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> RunestoneAmountText;
};
