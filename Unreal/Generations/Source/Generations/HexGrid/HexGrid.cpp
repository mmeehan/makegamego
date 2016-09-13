// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGrid.h"
#include "HexTile.h"

// Sets default values
AHexGrid::AHexGrid(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	
}

void AHexGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (!IsValid(world))
	{
		return;
	}

	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = this;

	const float sqrtOfThree = FMath::Sqrt(3.f);
	
	for (int32 q = -GridRadius; q <= GridRadius; q++)
	{
		for (int32 r = -GridRadius; r <= GridRadius; r++)
		{
			if (FMath::Abs(q + r) > GridRadius)
			{
				// simple check to make it 'circular'.
				continue;
			}

			const FVector Location(
				sqrtOfThree * (q + .5f * r),
				3 * r * .5f,
				0.f
			);

			const FVector ScaledLocation = Location * TileScale * (1.f + TileSpacing);

			UE_LOG(LogTemp, Log, TEXT("Spawning hex tile at %s"), *ScaledLocation.ToString());
			AHexTile* tile = world->SpawnActor<AHexTile>(TileActorClass, ScaledLocation, FRotator::ZeroRotator, spawnParameters);
			if (!IsValid(tile))
			{
				UE_LOG(LogTemp, Error, TEXT("Tile actor was not valid!"));
				continue;
			}

			tiles.Add(tile);
		}
	}
}

