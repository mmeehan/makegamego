// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HexGridCoordinate.h"
#include "HexNeighborDirection.h"
#include "HexTile.generated.h"

UCLASS()
class GENERATIONS_API AHexTile : public AActor
{
	GENERATED_BODY()
	
private:
	FHexGridCoordinate coordinates;
	TArray<TWeakObjectPtr<const AHexTile>> neighbors;

public:	
	AHexTile(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = Debug)
	void AssignDebugText(const FString& text);

	void SetCoordinates(const FHexGridCoordinate& coord);
	const FHexGridCoordinate GetCoordinates() const;

	void SetNeighbor(const EHexNeighborDirection direction, const AHexTile& neighbor);
	TWeakObjectPtr<const AHexTile> GetNeighbor(const EHexNeighborDirection direction) const;

	void AddGridMeshGeometry(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector>& normals, TArray<FColor>& colors) const;
	void AddEdgeMeshGeometry(TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector>& normals) const;

protected:
	
private:
	FVector GetNeighborCenterPosition(const EHexNeighborDirection direction) const;
};
