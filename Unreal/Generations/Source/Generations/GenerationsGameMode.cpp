// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "GenerationsGameMode.h"
#include "HexGrid/HexGrid.h"


void AGenerationsGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (!IsValid(world))
	{
		return;
	}

	world->SpawnActor<AHexGrid>(HexGridClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

