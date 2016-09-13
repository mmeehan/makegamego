// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexTile.h"
#include "CustomMeshComponent.h"

AHexTile::AHexTile(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PrimaryActorTick.bCanEverTick = true;

	mesh = ObjectInitializer.CreateDefaultSubobject<UCustomMeshComponent>(this, TEXT("GeneratedMesh"));

	// Hardcoded math for a y-axis aligned regular hexagon's corners
	const float xOffsetSides = FMath::Sqrt(3.f) * 0.5f;
	const FVector North(0, 1, 0);
	const FVector NorthEast(xOffsetSides, .5f, 0);
	const FVector SouthEast(xOffsetSides, -.5f, 0);
	const FVector South(0, -1, 0);
	const FVector SouthWest(-xOffsetSides, -.5f, 0);
	const FVector NorthWest(-xOffsetSides, .5f, 0);

	TArray<FCustomMeshTriangle> triangles;
	triangles.Add(FCustomMeshTriangle{ North, NorthEast, SouthEast });
	triangles.Add(FCustomMeshTriangle{ North, SouthEast, South });
	triangles.Add(FCustomMeshTriangle{ North, South, SouthWest });
	triangles.Add(FCustomMeshTriangle{ North, SouthWest, NorthWest });
	
	mesh->SetCustomMeshTriangles(triangles);

	FinishAndRegisterComponent(mesh);

	RootComponent = mesh;
}

void AHexTile::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* material = GetMaterialFromBlueprint();
	if (IsValid(material))
	{
		mesh->SetMaterial(0, material);
	}
}