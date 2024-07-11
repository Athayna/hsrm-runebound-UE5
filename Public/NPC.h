#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"

#include "Components/BoxComponent.h"

#include "NPC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogDelegate, FString&, Dialog);

/**
 * @brief A non-playable character that can be interacted with
 */
UCLASS(Blueprintable)
class RUNEBOUND_API ANPC : public AInteractable
{
	GENERATED_BODY()

public:
	/** Constructor */
	ANPC();

	/** Destructor */
	virtual ~ANPC() = default;

	/** Box collider to detect player interaction */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UBoxComponent> BoxCollider;

	/** Skeletal mesh of the NPC */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

	/** Delegate for when an NPC is talked to */
	FOnDialogDelegate OnDialog;

protected:
	/** Array of dialogue lines */
	UPROPERTY(EditAnywhere, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	TArray<FString> DialogueLines;
};