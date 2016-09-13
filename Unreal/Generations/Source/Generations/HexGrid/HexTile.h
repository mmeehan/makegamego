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
	UPROPERTY(BlueprintReadonly, Category=HexGrid)
	class UCustomMeshComponent* mesh;

	UFUNCTION(BlueprintImplementableEvent, Category=HexGrid)
	class UMaterialInterface* GetMaterialFromBlueprint();
};
