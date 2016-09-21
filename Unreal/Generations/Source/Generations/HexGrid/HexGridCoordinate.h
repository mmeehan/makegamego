// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexNeighborDirection.h"
#include "HexGridCoordinate.generated.h"

USTRUCT()
struct GENERATIONS_API FHexGridCoordinate
{
	GENERATED_USTRUCT_BODY()

private:
	int32 q;
	int32 r;

public:
	FHexGridCoordinate();
	FHexGridCoordinate(int32 _q, int32 _r);
	FHexGridCoordinate(const FHexGridCoordinate& Other);
	~FHexGridCoordinate();

	int32 Q() const;
	int32 R() const;
	
	FHexGridCoordinate Northeast() const;
	FHexGridCoordinate East() const;
	FHexGridCoordinate Southeast() const;
	FHexGridCoordinate Southwest() const;
	FHexGridCoordinate West() const;
	FHexGridCoordinate Northwest() const;
	FHexGridCoordinate Direction(const EHexNeighborDirection direction) const;
	FVector ToWorldSpace() const;

	bool operator==(const FHexGridCoordinate& Other) const;
};

FORCEINLINE uint32 GetTypeHash(const FHexGridCoordinate& Coord)
{
	return FCrc::MemCrc32(&Coord, sizeof(FHexGridCoordinate));
}