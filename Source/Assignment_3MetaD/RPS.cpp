// Fill out your copyright notice in the Description page of Project Settings.

#include "RPS.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ARPS::ARPS()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer = false;

	DefaultPawnClass = APlayerPawn::StaticClass();

	bAdvAI = false;

}