// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"

UCLASS()
class GENERATIONS_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AHexGrid(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Hexes)
	class TSubclassOf<class AHexTile> TileActorClass;

	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	int32 GridRadius;

	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	struct FVector TileScale;

	UPROPERTY(EditDefaultsOnly, Category = Hexes)
	float TileSpacing;

private:
	class TArray<class AHexTile*> tiles;
};
