#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "OldMan.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API AOldMan : public ANPC
{
	GENERATED_BODY()
	
public:
	/** COnstructor */
	AOldMan();

	/** Destructor */
	virtual ~AOldMan() = default;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

	/** Function to enable the chest attached to the old man */
	void EnableOldMan();

protected:
	/** Called when the game starts or when spawned */
	void BeginPlay() override;

private:
	/** Reference to the chest attached to the mage */
	UPROPERTY(VisibleAnywhere, Category = "OldMan")
	class AChest* Chest;
};
