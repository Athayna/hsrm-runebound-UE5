#include "InteractablePrompt.h"

#include "Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"
#include "Components/WidgetComponent.h"

void UInteractablePrompt::NativeConstruct()
{
    Super::NativeConstruct();
    RootWidget->SetVisibility(ESlateVisibility::Hidden);

    // Get all Interactable actors in the level and add a dynamic delegate to the OnActorBeginOverlap and OnActorEndOverlap events
    TArray<AActor*> Interactables = TArray<AActor*>();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractable::StaticClass(), Interactables);

    for (auto Actor : Interactables)
    {
        AInteractable* Interactable = Cast<AInteractable>(Actor);
        if (!Interactable) continue;
        Interactable->OnActorBeginOverlap.AddDynamic(this, &UInteractablePrompt::ShowPrompt);
        Interactable->OnActorEndOverlap.AddDynamic(this, &UInteractablePrompt::HidePrompt);
    }
}

void UInteractablePrompt::ShowPrompt(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OverlappedActor->IsA<AInteractable>())
    {
        AInteractable* Interactable = Cast<AInteractable>(OverlappedActor);
        if (!Interactable) return;

        if (Interactable->GetCollectable()) PromptText->SetText(FText::FromString("Collect"));
        else PromptText->SetText(FText::FromString("Interact"));

        RootWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInteractablePrompt::HidePrompt(AActor* OverlappedActor, AActor* OtherActor)
{
    RootWidget->SetVisibility(ESlateVisibility::Hidden);
}
