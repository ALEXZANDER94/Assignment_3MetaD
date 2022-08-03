// Fill out your copyright notice in the Description page of Project Settings.


#include "RPSChoice.h"

// Sets default values
ARPSChoice::ARPSChoice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RPSMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RPSMesh"));
	RPSMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARPSChoice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPSChoice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

