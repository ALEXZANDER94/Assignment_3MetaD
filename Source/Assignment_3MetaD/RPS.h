// Fill ou	t your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPS.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_3METAD_API ARPS : public AGameModeBase
{
	GENERATED_BODY()

	ARPS();

	private:
	
		bool bAdvAI;

	public:

		void SetAdvancedAI(bool adv) { bAdvAI = adv; };
		bool GetAdvancedAI() { return bAdvAI; }

};
