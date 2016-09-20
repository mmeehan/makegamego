// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct GENERATIONS_API FHexGridCoordinate
{
public:
	FHexGridCoordinate(int32 _q, int32 _r);
	~FHexGridCoordinate();

	const int32 q;
	const int32 r;

	FHexGridCoordinate Northeast() const;
	FHexGridCoordinate East() const;
	FHexGridCoordinate Southeast() const;
	FHexGridCoordinate Southwest() const;
	FHexGridCoordinate West() const;
	FHexGridCoordinate Northwest() const;
	FVector ToWorldSpace() const;
};
