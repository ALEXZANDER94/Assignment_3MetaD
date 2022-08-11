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

	RPSLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RPSSpotLight"));
	RPSLight->SetupAttachment(RPSMesh);
	RPSLight->SetIntensity(500.f);
	RPSLight->SetRelativeLocation(FVector(0, 0, 25.f));
	RPSLight->SetRelativeRotation(FRotator(-90.f, 0, 0));
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
	/* Need to Propagate the SetRenderCustomDepth to all children as well */
	TArray<UStaticMeshComponent*> ChildComps;
	GetComponents(ChildComps, true);
	/* Now that we have the Components, Need to iterate over them and apply the custom depth */
	for (int obj = 0; obj < ChildComps.Num(); obj++)
	{
		if (ChildComps[obj]->StaticClass()->GetName() == "StaticMeshComponent")
		{
			ChildComps[obj]->SetRenderCustomDepth(true);
		}
	}
}
void ARPSChoice::HideOutline()
{
	/* Need to Propagate the SetRenderCustomDepth to all children as well */
	TArray<UStaticMeshComponent*> ChildComps;
	GetComponents(ChildComps, true);
	/* Now that we have the Components, Need to iterate over them and apply the custom depth */
	for (int obj = 0; obj < ChildComps.Num(); obj++)
	{
		if (ChildComps[obj]->StaticClass()->GetName() == "StaticMeshComponent")
		{
			ChildComps[obj]->SetRenderCustomDepth(false);
		}
	}
}


