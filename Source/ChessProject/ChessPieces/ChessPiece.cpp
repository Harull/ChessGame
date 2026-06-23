// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/FloatingPawnMovement.h>

// Sets default values
AChessPiece::AChessPiece()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	capsule->SetupAttachment(RootComponent);

	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>("Skeleton");
	skeleton->SetupAttachment(capsule);

	movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	AddOwnedComponent(movement);
}

