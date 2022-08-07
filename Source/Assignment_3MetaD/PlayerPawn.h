// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Public/RPSChoice.h"
#include "Camera/CameraComponent.h"
#include <Assignment_3MetaD/Public/RPSType.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARPSChoice* RockPlayerChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARPSChoice* PaperPlayerChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARPSChoice* ScissorsPlayerChoice;

	void TurnRight(float delta);

	void MakeChoice(uint8 choice);
	DECLARE_DELEGATE_OneParam(ChoiceDelegate, uint8);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EType GetChoice() { return ChoiceType; }

	UFUNCTION()
	void TogglePlayerInput();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetChoice(EType choice);

	bool bPlayerEnabled = true;

private:

	EType ChoiceType;

};
