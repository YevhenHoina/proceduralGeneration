// Fill out your copyright notice in the Description page of Project Settings.


#include "defaultlTerrain.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AdefaultlTerrain::AdefaultlTerrain()
{
	PrimaryActorTick.bCanEverTick = false;

	Landscape = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	Landscape->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AdefaultlTerrain::BeginPlay()
{
	Super::BeginPlay();

	ConstructVeritces();
	ConstructTriangles();
	BuildLandscape();
	

}

// Called every frame
void AdefaultlTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AdefaultlTerrain::ConstructVeritces()
{
	float Z;
	for (int X = 0; X <= Size; X++)
	{
		for (int Y = 0; Y <= Size; Y++)
		{
			Z = Height * FMath::PerlinNoise2D(FVector2D((X + SEED) * 0.01, (Y + SEED) * 0.01)) + FMath::PerlinNoise2D(FVector2D(X * 0.1, Y * 0.1)) * TerrainSmoothness;
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * Size, Y * Size));

		}
	}
}

void AdefaultlTerrain::ConstructTriangles()
{
	int Vertex = 0;
	for (int Y = 0; Y < Size; Y++)
	{
		for (int X = 0; X < Size; X++)
		{
			Triangles.Add(Vertex + X);
			Triangles.Add(Vertex + X + 1);
			Triangles.Add(Vertex + X + Size + 1);
			Triangles.Add(Vertex + X + 1);
			Triangles.Add(Vertex + X + Size + 2);
			Triangles.Add(Vertex + X + Size + 1);
		}
		Vertex += (Size + 1);

	}
}

void AdefaultlTerrain::BuildLandscape()
{
	Landscape->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	Landscape->SetMaterial(0, Material);
}