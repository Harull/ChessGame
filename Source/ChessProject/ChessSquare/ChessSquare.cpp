// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessSquare.h"

// Sets default values
AChessSquare::AChessSquare()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChessSquare::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessSquare::InitializeBoardOwner(TObjectPtr<AChessboard> _owner)
{
	boardOwner = _owner;
}

