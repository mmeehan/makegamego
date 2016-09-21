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

void AddTriangle(TArray<int32>& triangles, int32 v0, int32 v1, int32 v2)
{
	triangles.Add(v0);
	triangles.Add(v1);
	triangles.Add(v2);
}

void AddEdgeTrapezoid(TArray<FVector>& vertices, TArray<int32>& triangles, const FVector& center, const FVector& firstPoint, const FVector& secondPoint)
{
	int firstOuterIndex = vertices.Add(firstPoint + FVector::UpVector);
	int secondOuterIndex = vertices.Add(secondPoint + FVector::UpVector);
	int firstInnerIndex = vertices.Add(FMath::Lerp(center, firstPoint, 0.95f) + FVector::UpVector);
	int secondInnerIndex = vertices.Add(FMath::Lerp(center, secondPoint, 0.95f) + FVector::UpVector);
	AddTriangle(triangles, firstOuterIndex, secondOuterIndex, secondInnerIndex);
	AddTriangle(triangles, secondInnerIndex, firstInnerIndex, firstOuterIndex);
}

void AHexTile::AddGridMeshGeometry(TArray<FVector>& vertices, TArray<int32>& triangles, TArray<FVector>& normals, TArray<FColor>& colors) const
{
	const FVector northEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northeast);
	const FVector eastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::East);
	const FVector southEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southeast);
	const FVector southWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southwest);
	const FVector westNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::West);
	const FVector northWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northwest);

	const FVector center = GetActorLocation();
	const FVector northCorner = (center + northEastNeighborPosition + northWestNeighborPosition) / 3.f;
	const FVector northEastBorder = (center + northEastNeighborPosition) / 2.f;
	const FVector northEastCorner = (center + northEastNeighborPosition + eastNeighborPosition) / 3.f;
	const FVector eastBorder = (center + eastNeighborPosition) / 2.f;
	const FVector southEastCorner = (center + eastNeighborPosition + southEastNeighborPosition) / 3.f;
	const FVector southEastBorder = (center + southEastNeighborPosition) / 2.f;
	const FVector southCorner = (center + southEastNeighborPosition + southWestNeighborPosition) / 3.f;
	const FVector southWestBorder = (center + southWestNeighborPosition) / 2.f;
	const FVector southWestCorner = (center + southWestNeighborPosition + westNeighborPosition) / 3.f;
	const FVector westBorder = (center + westNeighborPosition) / 2.f;
	const FVector northWestCorner = (center + northWestNeighborPosition + westNeighborPosition) / 3.f;
	const FVector northWestBorder = (center + northWestNeighborPosition) / 2.f;

	const int centerIndex = vertices.Add(center);
	const int northCornerIndex = vertices.Add(northCorner);
	const int northeastBorderIndex = vertices.Add(northEastBorder);
	const int northeastCornerIndex = vertices.Add(northEastCorner);
	const int eastBorderIndex = vertices.Add(eastBorder);
	const int southeastCornerIndex = vertices.Add(southEastCorner);
	const int southeastBorderIndex = vertices.Add(southEastBorder);
	const int southCornerIndex = vertices.Add(southCorner);
	const int southwestBorderIndex = vertices.Add(southWestBorder);
	const int southwestCornerIndex = vertices.Add(southWestCorner);
	const int westBorderIndex = vertices.Add(westBorder);
	const int northwestCornerIndex = vertices.Add(northWestCorner);
	const int northwestBorderIndex = vertices.Add(northWestBorder);

	AddTriangle(triangles, centerIndex, northCornerIndex, northeastBorderIndex);
	AddTriangle(triangles, centerIndex, northeastBorderIndex, northeastCornerIndex);
	AddTriangle(triangles, centerIndex, northeastCornerIndex, eastBorderIndex);
	AddTriangle(triangles, centerIndex, eastBorderIndex, southeastCornerIndex);
	AddTriangle(triangles, centerIndex, southeastCornerIndex, southeastBorderIndex);
	AddTriangle(triangles, centerIndex, southeastBorderIndex, southCornerIndex);
	AddTriangle(triangles, centerIndex, southCornerIndex, southwestBorderIndex);
	AddTriangle(triangles, centerIndex, southwestBorderIndex, southwestCornerIndex);
	AddTriangle(triangles, centerIndex, southwestCornerIndex, westBorderIndex);
	AddTriangle(triangles, centerIndex, westBorderIndex, northwestCornerIndex);
	AddTriangle(triangles, centerIndex, northwestCornerIndex, northwestBorderIndex);
	AddTriangle(triangles, centerIndex, northwestBorderIndex, northCornerIndex);

	normals.Add(FVector::UpVector);
	normals.Add(FVector::CrossProduct(northWestBorder - northCorner, center - northCorner));
	normals.Add(FVector::CrossProduct(northCorner - northEastBorder, center - northEastBorder));
	normals.Add(FVector::CrossProduct(northEastBorder - northEastCorner, center - northEastCorner));
	normals.Add(FVector::CrossProduct(northEastCorner - eastBorder, center - eastBorder));
	normals.Add(FVector::CrossProduct(eastBorder - southEastCorner, center - southEastCorner));
	normals.Add(FVector::CrossProduct(southEastCorner - southEastBorder, center - southEastBorder));
	normals.Add(FVector::CrossProduct(southEastBorder - southCorner, center - southCorner));
	normals.Add(FVector::CrossProduct(southCorner - southWestBorder, center - southWestBorder));
	normals.Add(FVector::CrossProduct(southWestBorder - southWestCorner, center - southWestCorner));
	normals.Add(FVector::CrossProduct(southWestCorner - westBorder, center - westBorder));
	normals.Add(FVector::CrossProduct(westBorder - northWestCorner, center - northWestCorner));
	normals.Add(FVector::CrossProduct(northWestCorner - northWestBorder, center - northWestBorder));

	colors.Add(ComputeColorFromHeight(center.Z));
	colors.Add(ComputeColorFromHeight(northCorner.Z));
	colors.Add(ComputeColorFromHeight(northEastBorder.Z));
	colors.Add(ComputeColorFromHeight(northEastCorner.Z));
	colors.Add(ComputeColorFromHeight(eastBorder.Z));
	colors.Add(ComputeColorFromHeight(southEastCorner.Z));
	colors.Add(ComputeColorFromHeight(southEastBorder.Z));
	colors.Add(ComputeColorFromHeight(southCorner.Z));
	colors.Add(ComputeColorFromHeight(southWestBorder.Z));
	colors.Add(ComputeColorFromHeight(southWestCorner.Z));
	colors.Add(ComputeColorFromHeight(westBorder.Z));
	colors.Add(ComputeColorFromHeight(northWestCorner.Z));
	colors.Add(ComputeColorFromHeight(northWestBorder.Z));
}

void AHexTile::AddEdgeMeshGeometry(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector>& normals) const
{
	const FVector northEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northeast);
	const FVector eastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::East);
	const FVector southEastNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southeast);
	const FVector southWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Southwest);
	const FVector westNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::West);
	const FVector northWestNeighborPosition = GetNeighborCenterPosition(EHexNeighborDirection::Northwest);

	const FVector center = GetActorLocation();
	const FVector northCorner = (center + northEastNeighborPosition + northWestNeighborPosition) / 3.f;
	const FVector northEastBorder = (center + northEastNeighborPosition) / 2.f;
	const FVector northEastCorner = (center + northEastNeighborPosition + eastNeighborPosition) / 3.f;
	const FVector eastBorder = (center + eastNeighborPosition) / 2.f;
	const FVector southEastCorner = (center + eastNeighborPosition + southEastNeighborPosition) / 3.f;
	const FVector southEastBorder = (center + southEastNeighborPosition) / 2.f;
	const FVector southCorner = (center + southEastNeighborPosition + southWestNeighborPosition) / 3.f;
	const FVector southWestBorder = (center + southWestNeighborPosition) / 2.f;
	const FVector southWestCorner = (center + southWestNeighborPosition + westNeighborPosition) / 3.f;
	const FVector westBorder = (center + westNeighborPosition) / 2.f;
	const FVector northWestCorner = (center + northWestNeighborPosition + westNeighborPosition) / 3.f;
	const FVector northWestBorder = (center + northWestNeighborPosition) / 2.f;

	AddEdgeTrapezoid(vertices, triangles, center, northCorner, northEastBorder);
	AddEdgeTrapezoid(vertices, triangles, center, northEastBorder, northEastCorner);
	AddEdgeTrapezoid(vertices, triangles, center, northEastCorner, eastBorder);
	AddEdgeTrapezoid(vertices, triangles, center, eastBorder, southEastCorner);
	AddEdgeTrapezoid(vertices, triangles, center, southEastCorner, southEastBorder);
	AddEdgeTrapezoid(vertices, triangles, center, southEastBorder, southCorner);
	AddEdgeTrapezoid(vertices, triangles, center, southCorner, southWestBorder);
	AddEdgeTrapezoid(vertices, triangles, center, southWestBorder, southWestCorner);
	AddEdgeTrapezoid(vertices, triangles, center, southWestCorner, westBorder);
	AddEdgeTrapezoid(vertices, triangles, center, westBorder, northWestCorner);
	AddEdgeTrapezoid(vertices, triangles, center, northWestCorner, northWestBorder);
	AddEdgeTrapezoid(vertices, triangles, center, northWestBorder, northCorner);
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