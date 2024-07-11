#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Plant.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API APlant : public AInteractable
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	APlant();

	/** Destructor */
	virtual ~APlant() = default;

	/** Called when the game starts or when spawned */
	virtual void Interact() override;

	/** Function to be called when the object is interacted with */
	UFUNCTION(BlueprintCallable, Category = "Plant")
	void EnablePlant();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Particle system to burn the plant */
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystemComponent* Fire;
};
