#include "Miasma.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include <Runebound/RuneboundCharacter.h>
#include "RuneboundGameState.h"

// Sets default values
AMiasma::AMiasma()
{
	// Create the root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	// Create the sphere collision component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(SceneRoot);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// Create the particle system component
	ParticleSystemComponent1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent1->SetupAttachment(SceneRoot);
	ParticleSystemComponent1->SetAutoActivate(true);

	ParticleSystemComponent2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent2"));
	ParticleSystemComponent2->SetupAttachment(SceneRoot);
	ParticleSystemComponent2->SetAutoActivate(true);

	// Set the function to be called when the sphere component begins to overlap another component
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMiasma::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMiasma::BeginPlay()
{
	Super::BeginPlay();
}

void AMiasma::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARuneboundGameState* GS = GetWorld()->GetGameState<ARuneboundGameState>())
	{
		if (GS->CheckInventory("InvisibilitySpell"))  // Check if the player has the InvisibilitySpell in their inventory
		{
			return;
		}

		// If the overlapping actor is the player, reset the player's position to the starting position
		else if (OtherActor->IsA(ARuneboundCharacter::StaticClass()))
		{
			if (ARuneboundCharacter* Player = Cast<ARuneboundCharacter>(OtherActor))
			{
				Player->SetActorLocation(FVector(2742.0f, 15059.0f, 0.0f));
			}
		}
	}
}



