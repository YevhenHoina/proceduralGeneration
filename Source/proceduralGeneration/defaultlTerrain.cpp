// Fill out your copyright notice in the Description page of Project Settings.


#include "defaultlTerrain.h"
#include "ProceduralMeshComponent.h"
#include "Containers/UnrealString.h"
#include "GameFramework/Actor.h"
#include <iostream>
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include <string>



// Sets default values
AdefaultlTerrain::AdefaultlTerrain()
{
	PrimaryActorTick.bCanEverTick = false;

	Landscape = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	Landscape->SetupAttachment(GetRootComponent());
}

void AdefaultlTerrain::OnConstruction(const FTransform& Transform)
{
// Called whet transform aplied
	Super::OnConstruction(Transform);

	FlushPersistentDebugLines(GetWorld());
	Vertices.Reset();
	Triangles.Reset();
	UV0.Reset();
	ShowChunks(true);

	
}
// Called when the game starts or when spawned
void AdefaultlTerrain::BeginPlay()
{
	Super::BeginPlay();

	ShowChunks(true);
	BuildChunk();
}

// Called every frame
void AdefaultlTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AdefaultlTerrain::ConstructVeritces()
{
	FVector global_position = GetActorLocation();
	float globalX = global_position.X / 100;
	float globalY = global_position.Y / 100;
	float globalZ;
	FString TheFloatStr = FString::SanitizeFloat(globalX);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *TheFloatStr);

	for (int X = 0; X <= Size; X++)
	{
		for (int Y = 0; Y <= Size; Y++)
		{
			globalZ = Height * FMath::PerlinNoise2D(FVector2D((globalX + X + 0.01) * 0.01, (globalY + Y + 0.01) * 0.01)) + TerrainSmoothness * FMath::PerlinNoise2D(FVector2D((globalX + 0.1), (globalY + 0.1)));
			Vertices.Add(FVector(X * Scale, Y * Scale, globalZ));
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

void AdefaultlTerrain::BuildChunk()
{
	ConstructVeritces();
	ConstructTriangles();
	Landscape->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	Landscape->SetMaterial(0, Material);
}

void AdefaultlTerrain::ShowChunks(bool shown) {
	
	if (shown) {
		FVector point1 = FVector(GetActorLocation().X, GetActorLocation().Y, -1000);
		FVector point2 = FVector(GetActorLocation().X, GetActorLocation().Y, 10000);
		DrawDebugLine(GetWorld(), point1, point2, FColor::Red, true, 100);

		//uncomment to show all lines
		/*point1 = FVector(GetActorLocation().X + Size * Scale, GetActorLocation().Y, -1000);
		point2 = FVector(GetActorLocation().X + Size * Scale, GetActorLocation().Y, 10000);
		DrawDebugLine(GetWorld(), point1, point2, FColor::Red, true, 100);

		point1 = FVector(GetActorLocation().X, GetActorLocation().Y + Size * Scale, -1000);
		point2 = FVector(GetActorLocation().X, GetActorLocation().Y + Size * Scale, 10000);
		DrawDebugLine(GetWorld(), point1, point2, FColor::Green, true, 100);

		point1 = FVector(GetActorLocation().X + Size * Scale, GetActorLocation().Y + Size * Scale, -1000);
		point2 = FVector(GetActorLocation().X + Size * Scale, GetActorLocation().Y + Size * Scale, 10000);
		DrawDebugLine(GetWorld(), point1, point2, FColor::Blue, true, 100);*/
	}


}