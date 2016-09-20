// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGridHeightMap.h"
#include "HexGridCoordinate.h"

HexGridHeightMap::HexGridHeightMap(int32 gridRadius, float minHeight, float maxHeight)
	: radius(gridRadius)
{
	int32 totalTiles = gridRadius * 2 + 1;
	totalTiles *= totalTiles;

	heights = new float[totalTiles];
	for (size_t index = 0; index < totalTiles; index++)
	{
		heights[index] = FMath::FRandRange(minHeight, maxHeight);
	}
}

HexGridHeightMap::~HexGridHeightMap()
{
	delete[] heights;
}

float HexGridHeightMap::GetHeight(const FHexGridCoordinate& coord, float heightIfOutOfBouds) const
{
	if (coord.q < -radius || coord.q > radius)
	{
		return heightIfOutOfBouds;
	}

	if (coord.r < -radius || coord.r > radius)
	{
		return heightIfOutOfBouds;
	}

	int32 totalTiles = (radius * 2) + 1;
	return heights[(coord.q + radius) * totalTiles + coord.r + radius];
}