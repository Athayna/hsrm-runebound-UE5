#pragma once

#include "CoreMinimal.h"
#include "Chest.h"

#include "Sound/SoundBase.h"

#include "CombinationChest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectCode);

/**
 * 
 */
UCLASS()
class RUNEBOUND_API ACombinationChest : public AChest
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	ACombinationChest();

	/** Destructor */
	virtual ~ACombinationChest() = default;

	/** Function to be called when the object is interacted with */
	virtual void Interact() override;

	/** Function to check the combination */
	UFUNCTION(BlueprintCallable, Category = "Combination")
	void CheckCode(TArray<int32> Code);

	/** Event to be called when the code is correct */
	UPROPERTY(BlueprintAssignable, Category = "Combination")
	FOnCorrectCode OnCorrectCode;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

private:
	/** Combination code */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combination", meta = (AllowPrivateAccess = "true"))
	TArray<int32> CombinationCode;

	/** Sound to play when the code is incorrect */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combination", meta = (AllowPrivateAccess = "true"))
	USoundBase* IncorrectCodeSound;
};
