#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API ARock : public AInteractable
{
	GENERATED_BODY()

public:
	/** Constructor */
	ARock();

	/** Destructor */
	virtual ~ARock() = default;

	/** Called when the game starts or when spawned */
	virtual void Interact() override;

	/** Function enabling the rock to be interacted with */
	UFUNCTION(BlueprintCallable, Category = "Rock")
	void EnableRock();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
};
