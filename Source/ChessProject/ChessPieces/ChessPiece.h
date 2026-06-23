// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChessPiece.generated.h"

class UCapsuleComponent;
class UFloatingPawnMovement;

UCLASS()
class CHESSPROJECT_API AChessPiece : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<UCapsuleComponent> capsule;
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<USkeletalMeshComponent> skeleton;
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<UFloatingPawnMovement> movement;

public:
	AChessPiece();

protected:

};
