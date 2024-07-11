#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Delegates/Delegate.h"

#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractedDelegate, AActor*, InteractedActor);

/**
 * @brief A base class for interactable objects
 */
UCLASS()
class RUNEBOUND_API AInteractable : public AActor
{
	GENERATED_BODY()

public:	
	/** Constructor */
	AInteractable();

	/** Destructor */
	virtual ~AInteractable() = default;

	/** Getter for bUniqueInteraction */
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool GetUniqueInteraction();
	
	/** Getter for bCollectable */
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool GetCollectable();

	/** Function to be called when the object is interacted with */
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual void Interact();

	/** Delegate for when the object is interacted with */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractedDelegate OnInteracted;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Sphere collider to detect player interaction */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollider;

	/** Static mesh of the object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Audio component for playing a sound when the object is interacted with */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> Audio;

	/** Root component of the object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	/** Variable to show if the object is only interactable once */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	bool bUniqueInteraction;

	/** Variable to show if the object is collectable and therefore destroyed after interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	bool bCollectable;
};
