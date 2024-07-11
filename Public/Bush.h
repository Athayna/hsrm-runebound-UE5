#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Bush.generated.h"

/** A bush that can play sounds when walked through */
UCLASS(Blueprintable, BlueprintType)
class RUNEBOUND_API ABush : public AActor
{
	GENERATED_BODY()

public:
	/** Constructor */
	ABush();

	/** Destructor */
	virtual ~ABush() = default;

	/** Audio component for playing a sound when the object is being walked through */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UAudioComponent> Audio;

	/** Sphere collider for the object */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USphereComponent> SphereCollider;

	/** Static mesh of the object */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Root component of the object */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> SceneRoot;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Function that is called when the actor is being overlapped by another actor */
	UFUNCTION(BlueprintCallable, Category="Default")
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};