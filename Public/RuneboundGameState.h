#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Delegates/Delegate.h"

#include "RuneboundGameState.generated.h"

USTRUCT()
struct FInventoryMap
{
	GENERATED_BODY()

	TMap<FString, int> Map;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveQuestChangedDelegate, const FString&, ActiveQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChangedDelegate, FInventoryMap&, InventoryMap);

UCLASS()
class RUNEBOUND_API ARuneboundGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** Constructor */
	ARuneboundGameState();

	/** Destructor */
	virtual ~ARuneboundGameState() = default;

	/** Delegate for when the active quest changes */
	FOnActiveQuestChangedDelegate OnActiveQuestChanged;

	/** Delegate for when the inventory changes */
	FOnInventoryChangedDelegate OnInventoryChanged;

	/** Function to increment the count of an item in the inventory map by 1 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void AddToInventory(FString ItemName);

	/** Function to remove an item from the inventory map */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void RemoveFromInventory(FString ItemName, int Count);

	/** Function to check if an item is in the inventory map */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool CheckInventory(FString ItemName) const;

	/** Function to get the count of an item in the inventory map */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual int GetInventoryCount(FString ItemName) const;

	/** Function to get the inventory map */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual TMap<FString, int> GetInventory() const;

	/** Setter for the active quest */
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetActiveQuest(FString Quest);

	/** Getter for the active quest */
	UFUNCTION(BlueprintCallable, Category = "Quest")
	FString GetActiveQuest() const;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

private:
	/** Inventory map to store the number of each collectable object */
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FInventoryMap Inventory;

	/** The currently active quest */
	UPROPERTY(VisibleAnywhere, Category = "Quest")
	FString ActiveQuest;
};
