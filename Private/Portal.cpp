#include "Portal.h"

#include "Kismet/GameplayStatics.h"

/**
 * @brief Constructor
 */
APortal::APortal()
{
    // Set the portal to be a unique interaction
    bUniqueInteraction = true;
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(StaticMesh);
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

/**
 * @brief Called when the game starts or when spawned
 */
void APortal::BeginPlay()
{
    Super::BeginPlay();

    PointLight->SetVisibility(false);
}

/**
 * @brief Function to be called when the object is interacted with. Teleports the player to the other portal.
 * 
 */
void APortal::Interact()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Result");
}

/**
 * @brief Enables the portal
 * @details Sets the point light to be visible and enables the sphere collider for collision detection
 */
void APortal::EnablePortal()
{
    PointLight->SetVisibility(true);
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Audio->Play();
}