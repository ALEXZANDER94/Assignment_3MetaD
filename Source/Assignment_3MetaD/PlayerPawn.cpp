// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include <Assignment_3MetaD/Public/RPSChoice.h>

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* set the UseControllerRotationYaw to false so theh player will rotate according to our defined rotate function */
	bUseControllerRotationYaw = false;

	/* Set the player pawn to be possessed by the player, there is only one so we can set the EAutoReceiveInput to 0 */

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	/* Define the Root Component as a Scene Component*/
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	/* Define the StaticMesh Component and Attach it to the Root*/
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetSimulatePhysics(true);
	Mesh->BodyInstance.bLockYRotation = true;
	Mesh->SetupAttachment(RootComponent);

	/* Define the Camera Component and Attach it to the Mesh */
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCam->SetRelativeRotation(FRotator(0, 0, 0));
	PlayerCam->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Begin Drawing a Raycast for checking if the player is looking at a choice for selection */
	FHitResult OutHit;
	
	/* Performing the Ray Cast requires a Start and End Vector 
	* Start is usually the Current Actor Location
	* End will be set to 500 units in the player's forward direction
	*/
	FVector StartLoc = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLoc = ((ForwardVector * 100.f) + StartLoc);

	FCollisionQueryParams Collisions;

	/* Draw Debug Line so we can visually see any collisions - remove for finished product */
	//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 1, 0, 2);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLoc, EndLoc, ECollisionChannel::ECC_GameTraceChannel1, Collisions);
	if(bHit)
	{
		AActor* HitActor = OutHit.GetActor();
		if (Cast<ARPSChoice>(HitActor)->ActorHasTag(TEXT("Choice")))
		{
			Cast<ARPSChoice>(HitActor)->ShowOutline();
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Choice: %s"), *UEnum::GetDisplayValueAsText(ChoiceType).ToString()));
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Bind Left/Right Input Axis to the TurnRight Function */
	InputComponent->BindAxis(TEXT("Left/Right"), this, &APlayerPawn::TurnRight);

	InputComponent->BindAction(TEXT("VisualChoice"), EInputEvent::IE_Pressed, this, &APlayerPawn::MakeChoice );
}

void APlayerPawn::TurnRight(float delta)
{
	if (delta)
	{
		AddActorLocalRotation(FRotator(0, delta, 0));
	}
}

void APlayerPawn::SetChoice(EType choice)
{
	ChoiceType = choice;
}

void APlayerPawn::MakeChoice()
{
	/* For the Make Choice, we need to draw another raycast to receive the select option */

	/* Begin Drawing a Raycast for checking if the player is looking at a choice for selection */
	FHitResult OutHit;

	/* Performing the Ray Cast requires a Start and End Vector
	* Start is usually the Current Actor Location
	* End will be set to 500 units in the player's forward direction
	*/
	FVector StartLoc = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLoc = ((ForwardVector * 100.f) + StartLoc);

	FCollisionQueryParams Collisions;

	/* Draw Debug Line so we can visually see any collisions - remove for finished product */
	//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 1, 0, 2);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLoc, EndLoc, ECollisionChannel::ECC_GameTraceChannel1, Collisions);
	if (bHit)
	{
		AActor* HitActor = OutHit.GetActor();
		if (Cast<ARPSChoice>(HitActor)->ActorHasTag(TEXT("Choice")))
		{
			SetChoice(Cast<ARPSChoice>(HitActor)->GetType());
		}
	}
}
