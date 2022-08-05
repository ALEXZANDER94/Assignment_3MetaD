// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPSType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EType : uint8
{
	Rock = 0		UMETA(DisplayName = "Rock"),
	Paper = 1		UMETA(DisplayName = "Paper"),
	Scissors = 2	UMETA(DisplayName = "Scissors")
};
UCLASS()
class ASSIGNMENT_3METAD_API URPSType : public UUserDefinedEnum
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EType RPSType;
};

