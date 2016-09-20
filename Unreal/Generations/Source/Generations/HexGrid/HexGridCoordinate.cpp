// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGridCoordinate.h"

FHexGridCoordinate::FHexGridCoordinate(int32 _q, int32 _r)
	: q(_q), r(_r)
{
}

FHexGridCoordinate::~FHexGridCoordinate()
{
}

FHexGridCoordinate FHexGridCoordinate::Northeast() const
{
	return FHexGridCoordinate(q, r + 1);
}

FHexGridCoordinate FHexGridCoordinate::East() const
{
	return FHexGridCoordinate(q + 1, r);
}

FHexGridCoordinate FHexGridCoordinate::Southeast() const
{
	return FHexGridCoordinate(q + 1, r - 1);
}

FHexGridCoordinate FHexGridCoordinate::Southwest() const
{
	return FHexGridCoordinate(q, r - 1);
}

FHexGridCoordinate FHexGridCoordinate::West() const
{
	return FHexGridCoordinate(q - 1, r);
}

FHexGridCoordinate FHexGridCoordinate::Northwest() const
{
	return FHexGridCoordinate(q - 1, r + 1);
}

FVector FHexGridCoordinate::ToWorldSpace() const
{
	const float sqrtOfThree = FMath::Sqrt(3.f);
	return FVector(
		sqrtOfThree * (q + .5f * r),
		3 * r * .5f,
		0.f
	);
}