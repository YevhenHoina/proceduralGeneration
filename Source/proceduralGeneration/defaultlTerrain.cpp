// Fill out your copyright notice in the Description page of Project Settings.


#include "defaultlTerrain.h"
#include "ProceduralMeshComponent.h"

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
	

}

// Called every frame
void AdefaultlTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

