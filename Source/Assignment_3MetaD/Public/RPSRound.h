// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assignment_3MetaD/PlayerPawn.h"
#include "Opponent.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "RPSRound.generated.h"

UENUM(BlueprintType)
enum class EStatus : uint8
{
	Draw = 0	UMETA(DisplayName = "Draw"),
	Lose = 1	UMETA(DisplayName = "Lose"),
	Win = 2		UMETA(DisplayName = "Win")
};

UENUM(BlueprintType)
enum class EMode : uint8
{
	BOf3 = 0	UMETA(DisplayName = "Best of 3"),
	BOf5 = 1	UMETA(DisplayName = "Best of 5"),
	FTo3 = 2	UMETA(DisplayName = "First to 3"),
	FTo5 = 3	UMETA(DisplayName = "First to 5"),
	Endless = 5	UMETA(DisplayName = "Endless")
};
UCLASS()
class ASSIGNMENT_3METAD_API URPSRound : public UGameInstance
{
	GENERATED_BODY()

	public:
		APlayerPawn* Player;
		AOpponent* Opp;
		
		void OpponentTurn();

		/* Have these function be blueprintcallable to use in UserWidgets */
		UFUNCTION(BlueprintCallable, BlueprintPure)
		FString GetStatus() { return RoundStatus; };

		UFUNCTION(BlueprintCallable, BlueprintPure)
		APlayerPawn* GetPlayer() { return Player; }

		UFUNCTION(BlueprintCallable, BlueprintPure)
		AOpponent* GetOpponent() { return Opp; }

		UFUNCTION(BlueprintCallable, BlueprintPure)
		EStatus GetPlayerWon() { return PlayerWon; }

		UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetPlayerWins() { return PlayerWins; }

		UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetPlayerLosses() { return PlayerLosses; }
		
		UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetDraws() { return DrawGames; }

		UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetRound() { return Round; }
		
		UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetAdvancedAI() { return bAdvancedAI; }

		UFUNCTION(BlueprintCallable)
		void SetAdvancedAI(bool advAI) { bAdvancedAI = advAI; }

		UFUNCTION(BlueprintCallable)
		void SetMode(EMode mode) { Mode = mode; }

		UFUNCTION(BlueprintCallable)
		bool GetGameOver() { return GameOver; }

		UFUNCTION(BlueprintCallable)
		void ResetGame();

		void PerformRoundAnim();

		UFUNCTION(BlueprintCallable)
		void CleanupRoundAnim();

	protected:
		void ResolveRound();
		void SetStatus(FString status) { RoundStatus = status; };
		void IncPlayerWins() { PlayerWins++; };
		void IncPlayerLosses() { PlayerLosses++; };
		void IncDrawGames() { DrawGames++; };
		void SetPlayerWon(EStatus won) { PlayerWon = won; };
		void SetGameOver(bool over) { GameOver = over; };
		void IncRounds() { Round++; };
		UFUNCTION(BlueprintCallable)
		void CheckGame();

	private:
		FString RoundStatus;
		int PlayerWins = 0;
		int PlayerLosses = 0;
		int DrawGames = 0;
		EStatus PlayerWon = EStatus::Draw;
		bool bAdvancedAI = false;
		EMode Mode = EMode::BOf3;
		bool GameOver = false;
		int Round = 1;
};
