#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API AChest : public AInteractable
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	AChest();

	/** Destructor */
	virtual ~AChest() = default;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Function to be called when the chest is opened */
	UFUNCTION(BlueprintCallable, Category = "Chest")
	virtual void OpenChest();

	/** Static mesh of the object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ChestTop;

	/** Array of collectables inside the chest */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chest", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> Loot;
};
