// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class GENERATIONS_API HexGridHeightMap
{
private:
	float* heights;

public:
	HexGridHeightMap(int32 gridRadius, float min, float max);
	~HexGridHeightMap();

	const int32 radius;
	const float minHeight;
	const float maxHeight;

	float GetHeight(const struct FHexGridCoordinate& coord, float heightIfOutOfBouds) const;
};
