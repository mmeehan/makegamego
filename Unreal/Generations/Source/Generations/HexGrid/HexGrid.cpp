// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGrid.h"
#include "HexTile.h"
#include "HexGridHeightMap.h"
#include "HexGridCoordinate.h"

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
	HexGridHeightMap heights(GridRadius, 0.6f, 1.2f);

	for (int32 q = -GridRadius; q <= GridRadius; q++)
	{
		for (int32 r = -GridRadius; r <= GridRadius; r++)
		{
			const FHexGridCoordinate coord(q, r);

			if (FMath::Abs(q + r) > GridRadius)
			{
				// simple check to make it 'circular'.
				continue;
			}

			const FVector Location = coord.ToWorldSpace();

			const FVector ScaledLocation = Location * TileScale * (1.f + TileSpacing);

			UE_LOG(LogTemp, Log, TEXT("Spawning hex tile at %s"), *ScaledLocation.ToString());
			AHexTile* tile = world->SpawnActor<AHexTile>(TileActorClass, ScaledLocation, FRotator::ZeroRotator, spawnParameters);
			if (!IsValid(tile))
			{
				UE_LOG(LogTemp, Error, TEXT("Tile actor was not valid!"));
				continue;
			}

			const float centerHeight = heights.GetHeight(coord, 0.f);
			const float northEastNeighborHeight = heights.GetHeight(coord.Northeast(), centerHeight);
			const float eastNeightborHeight = heights.GetHeight(coord.East(), centerHeight);
			const float southEastNeigborHeight = heights.GetHeight(coord.Southeast(), centerHeight);
			const float southWestNeigborHeight = heights.GetHeight(coord.Southwest(), centerHeight);
			const float westNeightborHeight = heights.GetHeight(coord.West(), centerHeight);
			const float northWestNeighborHeight = heights.GetHeight(coord.Northwest(), centerHeight);
			tile->AssignHeights(
				centerHeight, 
				northEastNeighborHeight, 
				eastNeightborHeight,
				southEastNeigborHeight, 
				southWestNeigborHeight,
				westNeightborHeight, 
				northWestNeighborHeight);

			tiles.Add(tile);

			tile->AssignDebugText(FString::Printf(TEXT("%i,%i"), q, r));
		}
	}
}

