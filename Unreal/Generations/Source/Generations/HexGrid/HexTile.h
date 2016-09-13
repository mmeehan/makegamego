// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HexTile.generated.h"

UCLASS()
class GENERATIONS_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHexTile(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Hexes)
	class USceneComponent* root;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Hexes)
	class UCustomMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Hexes)
	class UCustomMeshComponent* edgeMesh;

	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	struct FVector TileScale;

private:
	void AddSideTriangles(class TArray<struct FCustomMeshTriangle>& triangles, const FVector& corner1, const FVector& corner2);
	void AddEdgeTriangles(class TArray<struct FCustomMeshTriangle>& triangles, const FVector& center, const FVector& corner1, const FVector& corner2);
};
