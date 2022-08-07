#include "../Public/RPSRound.h"
#include "../RPS.h"
#include "../PlayerPawn.h"
#include "GameFramework/Actor.h"
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

	EStatus ePlayerWon = EStatus::Draw;
	FTimerHandle PlayerInputTimer;

	if (Player->GetChoice() == Opp->GetChoice())
	{
		/* Simplest thing to check for - Round Ends with a Draw */
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("The Round is a Draw."));
		SetStatus("The Round is a Draw");
		SetPlayerWon(EStatus::Draw);
		Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ToggleRoundResult();
		GetWorld()->GetTimerManager().SetTimer(PlayerInputTimer, Player, &APlayerPawn::TogglePlayerInput, 2.f, false);
		return;
	}

	/*	We only need to check for the conditions where the player wins,
	*	If none of these conditions are met and it's not a draw, then the player has lost.
	*/
	
	if ((Player->GetChoice() == EType::Rock && Opp->GetChoice() == EType::Scissors) ||
		(Player->GetChoice() == EType::Paper && Opp->GetChoice() == EType::Rock) ||
		(Player->GetChoice() == EType::Scissors && Opp->GetChoice() == EType::Paper))
	{
		
		ePlayerWon = EStatus::Win;
	}
	else
	{
		ePlayerWon = EStatus::Lose;
	}

	if (ePlayerWon == EStatus::Win)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("You've Won the Round."));
		SetStatus("You've Won The Round");
		SetPlayerWon(EStatus::Win);
		IncPlayerWins();
	}
	else if (ePlayerWon == EStatus::Lose)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You've Lost the Round."));
		SetStatus("You've Lost The Round");
		SetPlayerWon(EStatus::Lose);
		IncPlayerLosses();
	}
	Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ToggleRoundResult();
	/* Toggle the Player Input after 2 seconds */
	GetWorld()->GetTimerManager().SetTimer(PlayerInputTimer, Player, &APlayerPawn::TogglePlayerInput, 2.f, false);
	return;
}