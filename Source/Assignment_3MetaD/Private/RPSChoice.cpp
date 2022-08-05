// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/RPSChoice.h"

// Sets default values
ARPSChoice::ARPSChoice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	HitBox->InitBoxExtent(FVector(20, 10, 5));

	RootComponent = HitBox;

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
	HideOutline();

}

void ARPSChoice::ShowOutline()
{
	RPSMesh->SetRenderCustomDepth(true);
}
void ARPSChoice::HideOutline()
{
	RPSMesh->SetRenderCustomDepth(false);
}


