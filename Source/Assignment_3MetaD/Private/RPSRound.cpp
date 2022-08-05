// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/RPSRound.h"
#include "../RPS.h"
#include "Kismet/GameplayStatics.h"

void URPSRound::OpponentTurn()
{
	TArray<AActor*> OpponentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
	Opp = Cast<AOpponent>(OpponentActors[0]);

	Opp->MakeChoice();

	ResolveRound();
}

void URPSRound::ResolveRound()
{
	TArray<AActor*> OpponentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
	Opp = Cast<AOpponent>(OpponentActors[0]);

	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), PlayerActors);
	Player = Cast<APlayerPawn>(PlayerActors[0]);

	bool bPlayerWon = false;

	if (Player->GetChoice() == Opp->GetChoice())
	{
		/* Simplest thing to check for - Round Ends with a Draw */
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("The Round is a Draw."));
		SetStatus("The Round is a Draw");
		return;
	}

	/*	We only need to check for the conditions where the player wins,
	*	If none of these conditions are met and it's not a draw, then the player has lost.
	*/

	if ((Player->GetChoice() == EType::Rock && Opp->GetChoice() == EType::Scissors) ||
		(Player->GetChoice() == EType::Paper && Opp->GetChoice() == EType::Rock) ||
		(Player->GetChoice() == EType::Scissors && Opp->GetChoice() == EType::Paper)
		)
	{
		bPlayerWon = true;
	}

	if (bPlayerWon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("You've Won the Round."));
		SetStatus("You've Won The Round");
		IncPlayerWins();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You've Lost the Round."));
		SetStatus("You've Lost The Round");
		IncPlayerLosses();
	}

	Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ToggleRoundResult();
}