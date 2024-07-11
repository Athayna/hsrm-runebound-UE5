#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "Mage.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API AMage : public ANPC
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	AMage();

	/** Destructor */
	virtual ~AMage() = default;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

protected:
	/** Called when the game starts or when spawned */
	void BeginPlay() override;

private:
	/** Reference to the chest attached to the mage */
	UPROPERTY(VisibleAnywhere, Category = "Mage")
	class AChest* Chest;
};
