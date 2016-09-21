// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "HexGridCoordinate.h"
#include "HexGrid.generated.h"

UCLASS()
class GENERATIONS_API AHexGrid : public AActor
{
	GENERATED_BODY()

private:
	class TMap<FHexGridCoordinate, class AHexTile*> tiles;

public:	
	AHexGrid(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	class TSubclassOf<class AHexTile> TileActorClass;

	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	int32 GridRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hexes)
	UMaterialInstance* GridMeshMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hexes)
	UMaterialInstance* EdgeMeshMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Hexes)
	class UProceduralMeshComponent* EdgeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Hexes)
	class UProceduralMeshComponent* GridMesh;
};
