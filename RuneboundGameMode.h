#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RuneboundGameMode.generated.h"

/**
 * @brief The game mode for Runebound
 */
UCLASS()
class ARuneboundGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Constructor */
	ARuneboundGameMode();

	/** Desctructor */
	virtual ~ARuneboundGameMode() = default;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Function to be called when a collectable object is destroyed */
	UFUNCTION()
	void OnCollectableDestroyed(AActor* Collectable);

	/** Function to be called when an Interactable is being interacted with */
	UFUNCTION()
	void OnInteracted(AActor* Actor);

	/** Array to store all quests */
	UPROPERTY(VisibleAnywhere, Category = "Quest")
	TArray<FString> Quests;

	/** Reference to the Portal */
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class APortal* Portal;

	/** Reference to the OldMan */
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class AOldMan* OldMan;

	/** Reference to the Rock */
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class ARock* Rock;

	/** Reference to the Plant */
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class APlant* Plant;
};