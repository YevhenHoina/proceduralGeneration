// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "defaultlTerrain.generated.h"

class UProceduralMeshComponent;

UCLASS()
class PROCEDURALGENERATION_API AdefaultlTerrain : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AdefaultlTerrain();
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere)
	float SEED;
	UPROPERTY(EditAnywhere)
	int Size;
	UPROPERTY(EditAnywhere)
	int Scale;
	UPROPERTY(EditAnywhere)
	float Height;
	UPROPERTY(EditAnywhere)
	float TerrainSmoothness = 1;
	UPROPERTY(EditAnywhere)
	float Param;
	
private:
	UProceduralMeshComponent* Landscape;
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UV0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ShowChunks(bool shown);

private:
	void ConstructVeritces();
	void ConstructTriangles();
	void BuildChunk();
};
