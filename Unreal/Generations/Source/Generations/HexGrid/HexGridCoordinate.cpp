// Fill out your copyright notice in the Description page of Project Settings.

#include "Generations.h"
#include "HexGridCoordinate.h"

FHexGridCoordinate::FHexGridCoordinate()
	: q(0), r(0)
{
}

FHexGridCoordinate::FHexGridCoordinate(int32 _q, int32 _r)
	: q(_q), r(_r)
{
}

FHexGridCoordinate::FHexGridCoordinate(const FHexGridCoordinate& Other)
	: q(Other.q), r(Other.r)
{
}

FHexGridCoordinate::~FHexGridCoordinate()
{
}

int32 FHexGridCoordinate::Q() const
{
	return q;
}

int32 FHexGridCoordinate::R() const
{
	return r;
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

FHexGridCoordinate FHexGridCoordinate::Direction(const EHexNeighborDirection direction) const
{
	switch (direction)
	{
	case EHexNeighborDirection::Northeast:
		return Northeast();
	case EHexNeighborDirection::East:
		return East();
	case EHexNeighborDirection::Southeast:
		return Southeast();
	case EHexNeighborDirection::Southwest:
		return Southwest();
	case EHexNeighborDirection::West:
		return West();
	case EHexNeighborDirection::Northwest:
		return Northwest();
	}

	return FHexGridCoordinate(q, r);
}

FVector FHexGridCoordinate::ToWorldSpace() const
{
	const float sqrtOfThree = FMath::Sqrt(3.f);
	return FVector(
		sqrtOfThree * (q + .5f * r) * 200.f,
		3 * r * .5f * 200.f,
		0.f
	);
}

FORCEINLINE bool FHexGridCoordinate::operator==(const FHexGridCoordinate& Other) const
{
	return Other.q == q && Other.r == r;
}