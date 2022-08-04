// Fill out your copyright notice in the Description page of Project Settings.


#include "RPSRound.h"
#include "Kismet/GameplayStatics.h"

void URPSRound::OpponentTurn()
{
	TArray<AActor*> OpponentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOpponent::StaticClass(), OpponentActors);
	Opp = Cast<AOpponent>(OpponentActors[0]);

	Opp->MakeChoice();
}