#include "NPC.h"

ANPC::ANPC()
{
    // Override the sphere collider from the base class
    SphereCollider->DestroyComponent(); // Destroy the sphere collider from the base class
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider")); // Create a box collider

    // Override the static mesh from the base class
    StaticMesh->DestroyComponent(); // Destroy the static mesh from the base class
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh")); // Create a skeletal mesh

    SkeletalMesh->SetupAttachment(SceneRoot);   // Attach the skeletal mesh to the scene root
    BoxCollider->SetupAttachment(SkeletalMesh); // Attach the box collider to the skeletal mesh

    // Fill the dialogue lines array
    DialogueLines.Add("I heard there is a treasure in the forest, enshrouded by deadly miasma. The mage in the village might know how to traverse it.");
    DialogueLines.Add("Maybe the retired mage by the carpentry can help you with the miasma. She's been there before.");
    DialogueLines.Add("Shouldn't the adventurer be back by now? He's usually at the marketplace by his house. If not, look for him later");
    DialogueLines.Add("This old adventurer keeps babbiling about a rune stone or something. Wonder if he's back by now.");
}

void ANPC::Interact()
{
    // Call the base class function
    Super::Interact();

    // Get a random dialogue line
    FString Dialog = DialogueLines[FMath::RandRange(0, DialogueLines.Num() - 1)];

    // Broadcast the dialog event
    if (OnDialog.IsBound()) OnDialog.Broadcast(Dialog);

    // Print a random dialogue line
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Dialog);
}