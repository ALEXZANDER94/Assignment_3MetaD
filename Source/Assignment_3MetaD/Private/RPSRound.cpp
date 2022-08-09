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
		SetStatus("The Round is a Draw");
		SetPlayerWon(EStatus::Draw);
		IncDrawGames();
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
		SetStatus("You've Won The Round");
		SetPlayerWon(EStatus::Win);
		IncPlayerWins();
	}
	else if (ePlayerWon == EStatus::Lose)
	{
		SetStatus("You've Lost The Round");
		SetPlayerWon(EStatus::Lose);
		IncPlayerLosses();
	}
	Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ToggleRoundResult();
	/* Toggle the Player Input after 2 seconds */
	GetWorld()->GetTimerManager().SetTimer(PlayerInputTimer, Player, &APlayerPawn::TogglePlayerInput, 2.f, false);
	return;
}

void URPSRound::CheckGame()
{
	EStatus GameResult;
	switch (Mode)
	{
		case EMode::BOf3:
			if (Round == 3)
			{
				GameResult = (PlayerWins == PlayerLosses) ? EStatus::Draw : (PlayerWins > PlayerLosses) ? EStatus::Win : EStatus::Lose;
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(GameResult);
				GetPlayer()->TogglePlayerInput();
			}
			break;
		case EMode::BOf5:
			if (Round == 5)
			{
				GameResult = (PlayerWins == PlayerLosses) ? EStatus::Draw : (PlayerWins > PlayerLosses) ? EStatus::Win : EStatus::Lose;
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(GameResult);
				GetPlayer()->TogglePlayerInput();
			}
			break;
		case EMode::FTo3:
			if (PlayerWins >= 3)
			{
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(EStatus::Win);
				GetPlayer()->TogglePlayerInput();
			}
			else if (PlayerLosses >= 3)
			{
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(EStatus::Lose);
				GetPlayer()->TogglePlayerInput();
			}
			break;
		case EMode::FTo5:
			if (PlayerWins >= 5)
			{
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(EStatus::Win);
				GetPlayer()->TogglePlayerInput();
			}
			else if (PlayerLosses >= 5)
			{
				Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ShowGameOver(EStatus::Lose);
				GetPlayer()->TogglePlayerInput();
			}
			break;
		case EMode::Endless:
			break;
	}
	IncRounds();
}

void URPSRound::ResetGame()
{
	//Reset all the game variables and toggle the Player Input again.
	RoundStatus = "";
	PlayerWins = 0;
	PlayerLosses = 0;
	DrawGames = 0;
	PlayerWon = EStatus::Draw;
	GameOver = false;
	Round = 1;

	GetPlayer()->TogglePlayerInput();
}