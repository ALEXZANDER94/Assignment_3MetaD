// Fill out your copyright notice in the Description page of Project Settings.

#include "Opponent.h"
#include "../RPS.h"
#include "OpponentAI.h"
#include "Kismet/GameplayStatics.h"

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
	if (Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->GetAdvancedAI())
	{
		SetChoice(OpponentAI->GetFuzzyChoice());
	}
	else
	{
		SetChoice(OpponentAI->GetRandomChoice());
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Choice: %s"), *UEnum::GetDisplayValueAsText(ChoiceType).ToString()));
}

