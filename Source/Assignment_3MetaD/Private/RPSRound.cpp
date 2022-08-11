#include "../Public/RPSRound.h"
#include "../RPS.h"
#include "../PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void URPSRound::OpponentTurn()
{
	TArray<AActor*> OpponentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
	Opp = Cast<AOpponent>(OpponentActors[0]);

	Opp->MakeChoice();

	//Perform Animations Here, before the round is resolved.
	//Gives the illusion that the round is unable to resolve until the visuals complete
	PerformRoundAnim();
}

void URPSRound::PerformRoundAnim()
{
	//To start the round off, toggle the Spot lights for the round
	//Get the Opponent
	if (!Opp)
	{
		TArray<AActor*> OpponentActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
		Opp = Cast<AOpponent>(OpponentActors[0]);
	}
	if (!Player)
	{
		//Get the Player
		TArray<AActor*> PlayerActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), PlayerActors);
		Player = Cast<APlayerPawn>(PlayerActors[0]);
	}
	//Toggle the Spot Light Intensities
	Player->GetChoiceObject()->ToggleIntensity(500.f);
	Opp->GetChoiceObject()->ToggleIntensity(500.f);

	//Run the Round Sequencer to have the choices move to the center
	Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->RoundSequencer();
}

void URPSRound::CleanupRoundAnim()
{
	//To clean up the Round, just reverse what was done.
	//Get the Opponent
	if (!Opp)
	{
		TArray<AActor*> OpponentActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
		Opp = Cast<AOpponent>(OpponentActors[0]);
	}
	if (!Player)
	{
		//Get the Player
		TArray<AActor*> PlayerActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), PlayerActors);
		Player = Cast<APlayerPawn>(PlayerActors[0]);
	}

	Player->GetChoiceObject()->ToggleIntensity(0.f);
	Opp->GetChoiceObject()->ToggleIntensity(0.f);

	ResolveRound();
}

void URPSRound::ResolveRound()
{
	//Get the Opponent
	if (!Opp)
	{
		TArray<AActor*> OpponentActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
		Opp = Cast<AOpponent>(OpponentActors[0]);
	}
	if (!Player)
	{
		//Get the Player
		TArray<AActor*> PlayerActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), PlayerActors);
		Player = Cast<APlayerPawn>(PlayerActors[0]);
	}

	//Set Default PlayerWon State and define a Timer for the toggling the player input
	//after the round result has been logged
	EStatus ePlayerWon = EStatus::Draw;
	FTimerHandle PlayerInputTimer;

	/*
	*	The Flow of a Round ending is to set the status text, the the PlayerWon State,
	*	Increment the appropriate counter, then send it to the Game to call the HUD Functions 
	*	For the Round Log
	*/

	/* Debugging Outputs to check the Player Choice and Opponent Choice */
	/*
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Player Choice: %s"), *UEnum::GetDisplayValueAsText(Player->GetChoice()).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Opp Choice: %s"), *UEnum::GetDisplayValueAsText(Opp->GetChoice()).ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Player Choice: %s"), *UKismetSystemLibrary::GetDisplayName(Player->GetChoiceObject())));
	*/

	if ((Player->GetChoice() == EType::Rock && Opp->GetChoice() == EType::Scissors) ||
		(Player->GetChoice() == EType::Paper && Opp->GetChoice() == EType::Rock) ||
		(Player->GetChoice() == EType::Scissors && Opp->GetChoice() == EType::Paper))
	{
		
		ePlayerWon = EStatus::Win;
	}
	else if (Player->GetChoice() == Opp->GetChoice())
	{
		ePlayerWon = EStatus::Draw;
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
	else
	{
		SetStatus("The Round is a Draw");
		SetPlayerWon(EStatus::Draw);
		IncDrawGames();
	}
	Cast<ARPS>(UGameplayStatics::GetGameMode(GetWorld()))->ToggleRoundResult();
	/* Toggle the Player Input after 2 seconds */
	GetWorld()->GetTimerManager().SetTimer(PlayerInputTimer, Player, &APlayerPawn::TogglePlayerInput, 2.f, false);
	return;
}

/*
*	This function checks to see if the game is over.
*	This could occur when the round is equal to a defined number
*	or a player has reached a number of wins.
*/
void URPSRound::CheckGame()
{
	/*
	* I really dislike that some of the code is being re-used, but different game modes
	* calls for different kinds of checks
	*/
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
	/* Increment the Rounds at the end of the game over being checked
	*/
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