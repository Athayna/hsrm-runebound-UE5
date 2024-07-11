#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "QuestUI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API UQuestUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	/** Function to update the active quest UI */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateActiveQuestUI(const FString& ActiveQuest);

	/** Text block to display the active quest */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ActiveQuestText;

	/** Root widget of the UI */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> RootWidget;
};
