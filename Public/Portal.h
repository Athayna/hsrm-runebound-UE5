#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"

#include "Components/PointLightComponent.h"

#include "Portal.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBOUND_API APortal : public AInteractable
{
	GENERATED_BODY()

public:
	/** Constructor */
	APortal();

	/** Destructor */
	virtual ~APortal() = default;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

	/** Function to enable the Portal */
	UFUNCTION(BlueprintCallable, Category="Portal")
	void EnablePortal();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Point light which shines when all runestones have been collected */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UPointLightComponent> PointLight;
};
