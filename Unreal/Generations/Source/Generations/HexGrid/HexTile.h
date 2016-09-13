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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(BlueprintReadonly, Category=HexTile)
	class UCustomMeshComponent* mesh;

	UFUNCTION(BlueprintImplementableEvent, Category=HexTile)
	class UMaterialInterface* GetMaterialFromBlueprint();
};
