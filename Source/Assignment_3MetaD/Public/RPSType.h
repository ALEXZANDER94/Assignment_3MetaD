// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPSType.generated.h"

/**
 * 
 */
UENUM()
enum class EType : uint8
{
	Rock		UMETA(DisplayName = "Rock"),
	Paper		UMETA(DisplayName = "Paper"),
	Scissors	UMETA(DisplayName = "Scissors")
};
UCLASS()
class ASSIGNMENT_3METAD_API URPSType : public UUserDefinedEnum
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EType RPSType;
};

