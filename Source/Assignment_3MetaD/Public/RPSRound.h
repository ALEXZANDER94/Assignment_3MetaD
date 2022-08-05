// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assignment_3MetaD/PlayerPawn.h"
#include "Opponent.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "RPSRound.generated.h"

/**
 * 
 */
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

	protected:
		void ResolveRound();
		void SetStatus(FString status) { RoundStatus = status; };
		void IncPlayerWins() { PlayerWins++; };
		void IncPlayerLosses() { PlayerLosses++; };

	private:
		FString RoundStatus;
		uint8 PlayerWins = 0;
		uint8 PlayerLosses = 0;
};
