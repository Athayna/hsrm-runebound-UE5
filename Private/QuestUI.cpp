#include "QuestUI.h"
#include "RuneboundGameState.h"

void UQuestUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Get the game state and set the UI to update based on the game state
    ARuneboundGameState* GS = Cast<ARuneboundGameState>(GetWorld()->GetGameState());

    if (GS) {
        ActiveQuestText->SetText(FText::FromString(GS->GetActiveQuest()));
        GS->OnActiveQuestChanged.AddDynamic(this, &UQuestUI::UpdateActiveQuestUI);

    }
}

void UQuestUI::UpdateActiveQuestUI(const FString& ActiveQuest)
{
    ActiveQuestText->SetText(FText::FromString(ActiveQuest));
}