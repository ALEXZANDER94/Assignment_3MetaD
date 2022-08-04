// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPSType.h"
#include "OpponentAI.h"
#include "Opponent.generated.h"

UCLASS()
class ASSIGNMENT_3METAD_API AOpponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpponent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OppMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetChoice(EType choice) { ChoiceType = choice; };

	void MakeChoice();

private:
	EType ChoiceType;

	UOpponentAI* OpponentAI;
};
