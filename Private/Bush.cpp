#include "Bush.h"

/**
 * @brief Constructor
 * @details Sets up the audio component, static mesh, and scene root. Binds the OnOverlapBegin function to the OnComponentBeginOverlap event of the static mesh
 */
ABush::ABush()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	
	SetRootComponent(SceneRoot);													// Set the scene root as the root component
	StaticMesh->SetupAttachment(SceneRoot);											// Attach the static mesh to the scene root
	Audio->SetupAttachment(StaticMesh);												// Attach the audio component to the static mesh
	SphereCollider->SetupAttachment(StaticMesh);									// Attach the sphere collider to the static mesh
	
	//StaticMesh->SetCollisionProfileName("OverlapAll"); 								// Set the collision profile of the static mesh to overlap all

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABush::OnOverlapBegin); 	// Bind the OnOverlapBegin function to the OnComponentBeginOverlap event of the static mesh

	Audio->bAutoActivate = false;													// Don't play the audio component on begin play
}

/**
 * @brief Function that is called when the game starts or when spawned
 * @details Stops the audio component from playing on begin play
 */
void ABush::BeginPlay()
{
	Super::BeginPlay();

 	Audio->Stop();	// Stop the audio component from playing on begin play
}

/**
 * @brief Function that is called when the actor is being overlapped by another actor
 * @details Plays the sound if it exists and is not already playing
 * 
 * @param OverlappedComponent The component that is being overlapped
 * @param OtherActor The actor that is overlapping
 * @param OtherComp The component of the actor that is overlapping
 * @param OtherBodyIndex The body index of the actor that is overlapping
 * @param bFromSweep Whether the overlap was from a sweep
 * @param SweepResult The result of the sweep
 */
void ABush::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if (Audio->Sound && !Audio->IsPlaying()) Audio->Play();	// Don't interrupt the sound if it is already playing

	if (Audio->Sound) 
	{
		if (Audio->IsPlaying())	Audio->Stop(); // Interrupt the sound if it is already playing
		
		Audio->Play();
	}
}