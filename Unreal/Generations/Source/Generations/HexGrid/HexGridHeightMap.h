// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class GENERATIONS_API HexGridHeightMap
{
private:
	float* heights;
	int32 radius;
public:
	HexGridHeightMap(int32 gridRadius, float minHeight, float maxHeight);
	~HexGridHeightMap();

	float GetHeight(const struct FHexGridCoordinate& coord, float heightIfOutOfBouds) const;
};
