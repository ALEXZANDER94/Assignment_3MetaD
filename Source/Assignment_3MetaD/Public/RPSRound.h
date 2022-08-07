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
		int GetRound() { return Round; }

	protected:
		void ResolveRound();
		void SetStatus(FString status) { RoundStatus = status; };
		void IncPlayerWins() { PlayerWins++; };
		void IncPlayerLosses() { PlayerLosses++; };
		void SetPlayerWon(EStatus won) { PlayerWon = won; };

		UFUNCTION(BlueprintCallable)
		void IncRounds() { Round++; };

	private:
		FString RoundStatus;
		int PlayerWins = 0;
		int PlayerLosses = 0;
		EStatus PlayerWon = EStatus::Draw;

		int Round = 1;
};
