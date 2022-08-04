// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assignment_3MetaD/PlayerPawn.h"
#include "Opponent.h"
#include "Engine/GameInstance.h"
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
};
