// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "RPSType.h"
#include "PlayerPawn.generated.h"

UCLASS()
class ASSIGNMENT_3METAD_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	void TurnRight(float delta);

	void MakeChoice(uint8 choice);
	DECLARE_DELEGATE_OneParam(ChoiceDelegate, uint8);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetChoice(EType choice);

private:

	EType ChoiceType;
};
