// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GenerationsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GENERATIONS_API AGenerationsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Hexes)
	class TSubclassOf<class AHexGrid> HexGridClass;	
};
