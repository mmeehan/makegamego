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

	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	GridMesh = ObjectInitializer.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("GridMesh"));
	EdgeMesh = ObjectInitializer.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("EdgeMesh"));

	GridMesh->SetupAttachment(RootComponent);
	EdgeMesh->SetupAttachment(RootComponent);

	FinishAndRegisterComponent(RootComponent);
	FinishAndRegisterComponent(GridMesh);
	FinishAndRegisterComponent(EdgeMesh);
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

	HexGridHeightMap heights(GridRadius, 0.f, 150.f);

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

			FVector Location = coord.ToWorldSpace();
			Location.Z = heights.GetHeight(coord, 0.f);

			UE_LOG(LogTemp, Log, TEXT("Spawning hex tile at %s"), *Location.ToString());
			AHexTile* tile = world->SpawnActor<AHexTile>(TileActorClass, Location, FRotator::ZeroRotator, spawnParameters);
			if (!IsValid(tile))
			{
				UE_LOG(LogTemp, Error, TEXT("Tile actor was not valid!"));
				continue;
			}

			tile->SetCoordinates(coord);
			tile->AssignDebugText(FString::Printf(TEXT("%i,%i"), q, r));

			tiles.Add(coord, tile);
		}
	}

	TArray<FVector> gridMeshVertices;
	TArray<int32> gridMeshTriangles;
	TArray<FVector> gridMeshNormals;
	TArray<FColor> gridMeshColors;

	TArray<FVector> edgeMeshVertices;
	TArray<int32> edgeMeshTriangles;
	TArray<FVector> edgeMeshNormals;

	for (TMap<FHexGridCoordinate, AHexTile*>::TConstIterator iter = tiles.CreateConstIterator(); iter; ++iter)
	{
		const FHexGridCoordinate coord = iter->Key;
		AHexTile* const tile = iter->Value;

		for (EHexNeighborDirection direction = (EHexNeighborDirection)0; (uint8)direction < HexNeighborDirections; direction = (EHexNeighborDirection)((uint8)direction + 1))
		{
			const FHexGridCoordinate neighborCoord = coord.Direction(direction);
			if (neighborCoord == coord)
			{
				continue;
			}

			AHexTile** neighborInMap = tiles.Find(neighborCoord);
			if (neighborInMap == nullptr)
			{
				continue;
			}

			AHexTile* neighbor = *neighborInMap;
			if (!IsValid(neighbor))
			{
				continue;
			}

			tile->SetNeighbor(direction, *neighbor);
		}

		tile->AddGridMeshGeometry(gridMeshVertices, gridMeshTriangles, gridMeshNormals, gridMeshColors);
		tile->AddEdgeMeshGeometry(edgeMeshVertices, edgeMeshTriangles, edgeMeshNormals);
	}

	GridMesh->CreateMeshSection(0, gridMeshVertices, gridMeshTriangles, gridMeshNormals, TArray<FVector2D>(), gridMeshColors, TArray<FProcMeshTangent>(), false);	
	EdgeMesh->CreateMeshSection(0, edgeMeshVertices, edgeMeshTriangles, edgeMeshNormals, TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);

	GridMesh->SetMaterial(0, GridMeshMaterial);
	EdgeMesh->SetMaterial(0, EdgeMeshMaterial);
}

