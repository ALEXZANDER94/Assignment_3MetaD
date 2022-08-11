// Fill ou	t your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/RPSRound.h"
#include "RPS.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_3METAD_API ARPS : public AGameModeBase
{
	GENERATED_BODY()

	ARPS();
	
	public:

		UFUNCTION(BlueprintImplementableEvent)
		void ToggleRoundResult();

		UFUNCTION(BlueprintImplementableEvent)
		void ShowGameOver(EStatus gameStatus);

		UFUNCTION(BlueprintImplementableEvent)
		void MoveLogUp();

		UFUNCTION(BlueprintImplementableEvent)
		void MoveLogDown();

		UFUNCTION(BlueprintImplementableEvent)
		void RoundSequencer();

		UFUNCTION(BlueprintImplementableEvent)
		void OppositionSequencer();

		UFUNCTION(BlueprintImplementableEvent)
		void CleanupSequencer();
};
