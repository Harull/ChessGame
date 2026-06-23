// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chessboard.h"
#include "ChessboardSquared.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AChessboardSquared : public AChessboard
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings") int chessboardSize = 8;
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AChessSquare> whiteSquare;
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AChessSquare> blackSquare;


public:
	virtual void GenerateBoard() override;

	


};
