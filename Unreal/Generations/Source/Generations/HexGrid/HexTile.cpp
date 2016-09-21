// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexTile.h"
#include "CustomMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "HexGridCoordinate.h"
#include "HexGridHeightMap.h"

AHexTile::AHexTile(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	neighbors.Init(nullptr, 6);
}

void AHexTile::BeginPlay()
{
	Super::BeginPlay();
}

//void AHexTile::AddEdgeTriangles(TArray<FCustomMeshTriangle>& triangles, const FVector& center, const FVector& corner1, const FVector& corner2)
//{
//	const FVector SlightUp(0.f, 0.f, 0.001f);
//	const FVector centerUp = center + SlightUp;
//	const FVector corner1Up = corner1 + SlightUp;
//	const FVector corner2Up = corner2 + SlightUp;
//
//	const FVector corner1In = FMath::Lerp(centerUp, corner1Up, 0.9f);
//	const FVector corner2In = FMath::Lerp(centerUp, corner2Up, 0.9f);
//
//	triangles.Add(FCustomMeshTriangle{ corner1Up, corner2Up, corner2In });
//	triangles.Add(FCustomMeshTriangle{ corner2In, corner1In, corner1Up });
//}

FColor ComputeColorFromHeight(float height)
{
	const float alpha = (height / 150.f);
	const uint8 alphaByte = static_cast<uint8>(FMath::FloorToInt(alpha * 255));
	UE_LOG(LogTemp, Log, TEXT("Height %f => %i"), height, alphaByte);
	return FColor(alphaByte, alphaByte, alphaByte, alphaByte);
}

void AHexTile::SetCoordinates(const FHexGridCoordinate& coord)
{
	coordinates = coord;
}

const FHexGridCoordinate AHexTile::GetCoordinates() const
{
	return coordinates;
}

void AHexTile::SetNeighbor(const EHexNeighborDirection direction, const AHexTile& neighbor)
{
	neighbors[(uint8)direction] = &neighbor;
}

TWeakObjectPtr<const AHexTile> AHexTile::GetNeighbor(const EHexNeighborDirection direction) const
{
	return neighbors[(uint8)direction];
}

//void AHexTile::AssignHeights(
//	const FHexGridCoordinate& coord,
//	const HexGridHeightMap& heights)
//{
//	const float centerHeight = heights.GetHeight(coord, 0.f);
//	const float northEastNeighborHeight = heights.GetHeight(coord.Northeast(), centerHeight);
//	const float eastNeighborHeight = heights.GetHeight(coord.East(), centerHeight);
//	const float southEastNeighborHeight = heights.GetHeight(coord.Southeast(), centerHeight);
//	const float southWestNeighborHeight = heights.GetHeight(coord.Southwest(), centerHeight);
//	const float westNeighborHeight = heights.GetHeight(coord.West(), centerHeight);
//	const float northWestNeighborHeight = heights.GetHeight(coord.Northwest(), centerHeight);
//
//	// Hardcoded math for a y-axis aligned regular hexagon's corners
//	const float xOffsetSides = FMath::Sqrt(3.f) * 0.5f;
//	const FVector Center(0, 0, centerHeight);
//	const FVector North(0, 1, (centerHeight + northEastNeighborHeight + northWestNeighborHeight) / 3.f);
//	const FVector NorthEast(xOffsetSides, .5f, (centerHeight + northEastNeighborHeight + eastNeighborHeight) / 3.f);
//	const FVector SouthEast(xOffsetSides, -.5f, (centerHeight + eastNeighborHeight + southEastNeighborHeight) / 3.f);
//	const FVector South(0, -1, (centerHeight + southEastNeighborHeight + southWestNeighborHeight) / 3.f);
//	const FVector SouthWest(-xOffsetSides, -.5f, (centerHeight + southWestNeighborHeight + westNeighborHeight) / 3.f);
//	const FVector NorthWest(-xOffsetSides, .5f, (centerHeight + westNeighborHeight + northWestNeighborHeight) / 3.f);
//
//	TArray<FCustomMeshTriangle> edgeTriangles;
//	AddEdgeTriangles(edgeTriangles, Center, North, NorthEast);
//	AddEdgeTriangles(edgeTriangles, Center, NorthEast, SouthEast);
//	AddEdgeTriangles(edgeTriangles, Center, SouthEast, South);
//	AddEdgeTriangles(edgeTriangles, Center, South, SouthWest);
//	AddEdgeTriangles(edgeTriangles, Center, SouthWest, NorthWest);
//	AddEdgeTriangles(edgeTriangles, Center, NorthWest, North);
//
//	edgeMesh->SetCustomMeshTriangles(edgeTriangles);
//	edgeMesh->SetRelativeScale3D(TileScale);
//
//	TArray<FVector> vertices;
//	const int centerIndex = vertices.Add(Center);
//	const int northIndex = vertices.Add(North);
//	const int northeastIndex = vertices.Add(NorthEast);
//	const int southeastIndex = vertices.Add(SouthEast);
//	const int southIndex = vertices.Add(South);
//	const int southwestIndex = vertices.Add(SouthWest);
//	const int northwestIndex = vertices.Add(NorthWest);
//
//	TArray<int32> triangleIndices;
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(northIndex);
//	triangleIndices.Add(northeastIndex);
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(northeastIndex);
//	triangleIndices.Add(southeastIndex);
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(southeastIndex);
//	triangleIndices.Add(southIndex);
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(southIndex);
//	triangleIndices.Add(southwestIndex);
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(southwestIndex);
//	triangleIndices.Add(northwestIndex);
//	triangleIndices.Add(centerIndex);
//	triangleIndices.Add(northwestIndex);
//	triangleIndices.Add(northIndex);
//
//	TArray<FVector> normals;
//	normals.Add(FVector::UpVector);
//	normals.Add(FVector::CrossProduct(Center - North, NorthEast - North));
//	normals.Add(FVector::CrossProduct(Center - NorthEast, SouthEast - NorthEast));
//	normals.Add(FVector::CrossProduct(Center - SouthEast, South - SouthEast));
//	normals.Add(FVector::CrossProduct(Center - South, SouthWest - South));
//	normals.Add(FVector::CrossProduct(Center - SouthWest, NorthWest - SouthWest));
//	normals.Add(FVector::CrossProduct(Center - NorthWest, North - NorthWest));
//
//	TArray<FColor> colors;
//	colors.Add(ComputeColorFromHeight(heights, centerHeight));
//	colors.Add(ComputeColorFromHeight(heights, North.Z));
//	colors.Add(ComputeColorFromHeight(heights, NorthEast.Z));
//	colors.Add(ComputeColorFromHeight(heights, SouthEast.Z));
//	colors.Add(ComputeColorFromHeight(heights, South.Z));
//	colors.Add(ComputeColorFromHeight(heights, SouthWest.Z));
//	colors.Add(ComputeColorFromHeight(heights, NorthWest.Z));
//
//	proceduralMesh->CreateMeshSection(0, vertices, triangleIndices, normals, TArray<FVector2D>(), colors, TArray<FProcMeshTangent>(), false);
//	proceduralMesh->SetRelativeScale3D(TileScale);
//}

void AHexTile::AddGridMeshGeometry(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector>& normals, TArray<FColor>& colors) const
{
	const FVector northEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northeast);
	const FVector eastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::East);
	const FVector southEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southeast);
	const FVector southWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southwest);
	const FVector westNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::West);
	const FVector northWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northwest);

	const FVector center = GetActorLocation();
	const FVector north = (center + northEastNeighborPosition + northWestNeighborPosition) / 3.f;
	const FVector northEast = (center + northEastNeighborPosition + eastNeighborPosition) / 3.f;
	const FVector southEast = (center + eastNeighborPosition + southEastNeighborPosition) / 3.f;
	const FVector south = (center + southEastNeighborPosition + southWestNeighborPosition) / 3.f;
	const FVector southWest = (center + southWestNeighborPosition + westNeighborPosition) / 3.f;
	const FVector northWest = (center + northWestNeighborPosition + westNeighborPosition) / 3.f;

	const int centerIndex = vertices.Add(center);
	const int northIndex = vertices.Add(north);
	const int northeastIndex = vertices.Add(northEast);
	const int southeastIndex = vertices.Add(southEast);
	const int southIndex = vertices.Add(south);
	const int southwestIndex = vertices.Add(southWest);
	const int northwestIndex = vertices.Add(northWest);

	triangles.Add(centerIndex);
	triangles.Add(northIndex);
	triangles.Add(northeastIndex);
	triangles.Add(centerIndex);
	triangles.Add(northeastIndex);
	triangles.Add(southeastIndex);
	triangles.Add(centerIndex);
	triangles.Add(southeastIndex);
	triangles.Add(southIndex);
	triangles.Add(centerIndex);
	triangles.Add(southIndex);
	triangles.Add(southwestIndex);
	triangles.Add(centerIndex);
	triangles.Add(southwestIndex);
	triangles.Add(northwestIndex);
	triangles.Add(centerIndex);
	triangles.Add(northwestIndex);
	triangles.Add(northIndex);

	normals.Add(FVector::UpVector);
	normals.Add(FVector::CrossProduct(northEastNeighborPosition - center, northWestNeighborPosition - center));
	normals.Add(FVector::CrossProduct(eastNeighborPosition - center, northEastNeighborPosition - center));
	normals.Add(FVector::CrossProduct(southEastNeighborPosition - center, eastNeighborPosition - center));
	normals.Add(FVector::CrossProduct(southWestNeighborPosition - center, southEastNeighborPosition - center));
	normals.Add(FVector::CrossProduct(westNeighborPosition - center, southWestNeighborPosition - center));
	normals.Add(FVector::CrossProduct(northWestNeighborPosition - center, westNeighborPosition - center));

	colors.Add(ComputeColorFromHeight(center.Z));
	colors.Add(ComputeColorFromHeight(north.Z));
	colors.Add(ComputeColorFromHeight(northEast.Z));
	colors.Add(ComputeColorFromHeight(southEast.Z));
	colors.Add(ComputeColorFromHeight(south.Z));
	colors.Add(ComputeColorFromHeight(southWest.Z));
	colors.Add(ComputeColorFromHeight(northWest.Z));
}

void AHexTile::AddEdgeMeshGeometry(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector>& normals) const
{

}

FVector AHexTile::GetNeighborCenterPosition(const EHexNeighborDirection direction) const
{
	const TWeakObjectPtr<const AHexTile> neighbor = GetNeighbor(direction);
	if (neighbor.IsValid())
	{
		return neighbor->GetActorLocation();
	}

	FVector computedPosition = coordinates.Direction(direction).ToWorldSpace();
	computedPosition.Z = GetActorLocation().Z;
	return computedPosition;
}