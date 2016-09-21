// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGridHeightMap.h"
#include "HexGridCoordinate.h"

HexGridHeightMap::HexGridHeightMap(int32 gridRadius, float min, float max)
	: radius(gridRadius), minHeight(min), maxHeight(max)
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
	const int32 q = coord.Q();
	if (q < -radius || q > radius)
	{
		return heightIfOutOfBouds;
	}

	const int32 r = coord.R();
	if (r < -radius || r > radius)
	{
		return heightIfOutOfBouds;
	}

	int32 totalTiles = (radius * 2) + 1;
	return heights[(q + radius) * totalTiles + r + radius];
}