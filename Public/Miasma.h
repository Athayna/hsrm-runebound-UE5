#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Miasma.generated.h"

UCLASS()
class RUNEBOUND_API AMiasma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiasma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Particle system component 1 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miasma")
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent1;

	/** Particle system component 2 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miasma")
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent2;

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miasma")
	TObjectPtr<USphereComponent> SphereComponent;

	/** Root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miasma")
	TObjectPtr<USceneComponent> SceneRoot;

	/** Called when the sphere component begins to overlap another component */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
