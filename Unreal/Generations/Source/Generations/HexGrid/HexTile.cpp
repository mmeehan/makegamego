// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexTile.h"
#include "CustomMeshComponent.h"

AHexTile::AHexTile(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PrimaryActorTick.bCanEverTick = true;

	root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	mesh = ObjectInitializer.CreateDefaultSubobject<UCustomMeshComponent>(this, TEXT("Mesh"));
	edgeMesh = ObjectInitializer.CreateDefaultSubobject<UCustomMeshComponent>(this, TEXT("EdgeMesh"));

	RootComponent = root;
	mesh->SetupAttachment(root);
	edgeMesh->SetupAttachment(root);

	FinishAndRegisterComponent(root);
	FinishAndRegisterComponent(mesh);
	FinishAndRegisterComponent(edgeMesh);
}

void AHexTile::BeginPlay()
{
	Super::BeginPlay();

	const float randomHeight = FMath::FRandRange(0.8f, 1.2f);

	// Hardcoded math for a y-axis aligned regular hexagon's corners
	const float xOffsetSides = FMath::Sqrt(3.f) * 0.5f;
	const FVector Center(0, 0, randomHeight);
	const FVector North(0, 1, randomHeight);
	const FVector NorthEast(xOffsetSides, .5f, randomHeight);
	const FVector SouthEast(xOffsetSides, -.5f, randomHeight);
	const FVector South(0, -1, randomHeight);
	const FVector SouthWest(-xOffsetSides, -.5f, randomHeight);
	const FVector NorthWest(-xOffsetSides, .5f, randomHeight);

	TArray<FCustomMeshTriangle> triangles;
	triangles.Add(FCustomMeshTriangle{ North, NorthEast, SouthEast });
	triangles.Add(FCustomMeshTriangle{ North, SouthEast, South });
	triangles.Add(FCustomMeshTriangle{ North, South, SouthWest });
	triangles.Add(FCustomMeshTriangle{ North, SouthWest, NorthWest });

	AddSideTriangles(triangles, North, NorthEast);
	AddSideTriangles(triangles, NorthEast, SouthEast);
	AddSideTriangles(triangles, SouthEast, South);
	AddSideTriangles(triangles, South, SouthWest);
	AddSideTriangles(triangles, SouthWest, NorthWest);
	AddSideTriangles(triangles, NorthWest, North);

	mesh->SetCustomMeshTriangles(triangles);
	mesh->SetRelativeScale3D(TileScale);

	TArray<FCustomMeshTriangle> edgeTriangles;
	AddEdgeTriangles(edgeTriangles, Center, North, NorthEast);
	AddEdgeTriangles(edgeTriangles, Center, NorthEast, SouthEast);
	AddEdgeTriangles(edgeTriangles, Center, SouthEast, South);
	AddEdgeTriangles(edgeTriangles, Center, South, SouthWest);
	AddEdgeTriangles(edgeTriangles, Center, SouthWest, NorthWest);
	AddEdgeTriangles(edgeTriangles, Center, NorthWest, North);

	edgeMesh->SetCustomMeshTriangles(edgeTriangles);
	edgeMesh->SetRelativeScale3D(TileScale);
}

void AHexTile::AddSideTriangles(TArray<FCustomMeshTriangle>& triangles, const FVector& corner1, const FVector& corner2)
{
	const FVector corner1Down = corner1 - FVector::UpVector;
	const FVector corner2Down = corner2 - FVector::UpVector;

	triangles.Add(FCustomMeshTriangle{ corner1Down, corner2, corner1 });
	triangles.Add(FCustomMeshTriangle{ corner1Down, corner2Down, corner2 });
}

void AHexTile::AddEdgeTriangles(TArray<FCustomMeshTriangle>& triangles, const FVector& center, const FVector& corner1, const FVector& corner2)
{
	const FVector SlightUp(0.f, 0.f, 0.001f);
	const FVector centerUp = center + SlightUp;
	const FVector corner1Up = corner1 + SlightUp;
	const FVector corner2Up = corner2 + SlightUp;

	const FVector corner1In = FMath::Lerp(centerUp, corner1Up, 0.9f);
	const FVector corner2In = FMath::Lerp(centerUp, corner2Up, 0.9f);

	triangles.Add(FCustomMeshTriangle{ corner1Up, corner2Up, corner2In });
	triangles.Add(FCustomMeshTriangle{ corner2In, corner1In, corner1Up });
}