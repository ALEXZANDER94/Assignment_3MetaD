
#include "../Public/Opponent.h"
#include "../RPS.h"
#include "OpponentAI.h"
#include "Kismet/GameplayStatics.h"
#include <Assignment_3MetaD/Public/RPSRound.h>

// Sets default values
AOpponent::AOpponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OppMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OppMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AOpponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOpponent::MakeChoice()
{
	if (Cast<URPSRound>(UGameplayStatics::GetGameInstance(GetWorld()))->GetAdvancedAI())
	{
		SetChoice(OpponentAI->GetFuzzyChoice());
	}
	else
	{
		EType choice = OpponentAI->GetRandomChoice();
		SetChoice(choice);
		
		for (TActorIterator<ARPSChoice> ChoiceActor(GetWorld()); ChoiceActor; ++ChoiceActor)
		{
			ARPSChoice* ChoiceObj = *ChoiceActor;
			FString ChoiceTypeAsString = (choice == EType::Rock) ? TEXT("Rock") : (choice == EType::Paper) ? TEXT("Paper") : TEXT("Scissors");
			if (ChoiceObj->ActorHasTag("Opponent") && ChoiceObj->ActorHasTag(FName(*ChoiceTypeAsString)))
			{
				SetChoiceObject(ChoiceObj);
			}
		}
		
	}
	/* Debug Output to see what the Opponent Picked */
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Choice: %s"), *UEnum::GetDisplayValueAsText(ChoiceType).ToString()));
}

