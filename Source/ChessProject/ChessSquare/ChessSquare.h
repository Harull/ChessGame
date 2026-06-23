// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ChessProject/DataAssets/ChessMeshDataAsset.h>
#include "ChessSquare.generated.h"



USTRUCT(BlueprintType)
struct FCoordinates
{
	GENERATED_BODY()
public:
	FCoordinates() = default;
	FCoordinates(const int _x, const int _y)
	{
		x = _x;
		y = _y;
	}
public:
	UPROPERTY(VisibleAnywhere) int x;
	UPROPERTY(VisibleAnywhere) int y;
};


class AChessboard;
class AChessPiece;

UCLASS()
class CHESSPROJECT_API AChessSquare : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<UStaticMeshComponent> mesh;

	UPROPERTY(EditAnywhere, Category = "Settings") TEnumAsByte<ESquareType> squareType;

	//The chess piece currently on this square
	UPROPERTY(VisibleAnywhere, Category = "Debug") TObjectPtr<AChessPiece> chessPieceOnSquare;
	UPROPERTY(VisibleAnywhere, Category = "Debug") TObjectPtr<AChessboard> boardOwner;
	UPROPERTY(VisibleAnywhere, Category = "Debug") FCoordinates coordinates;

public:	
	// Sets default values for this actor's properties
	AChessSquare();

public:
	//Getters
	FORCEINLINE UPROPERTY(BlueprintCallable) TObjectPtr<AChessPiece> GetChessPieceOnSquare() const { return chessPieceOnSquare; }
	FORCEINLINE UPROPERTY(BlueprintCallable) TEnumAsByte<ESquareType> GetSquareType() const { return squareType; }
	FORCEINLINE UPROPERTY(BlueprintCallable) TObjectPtr<UStaticMeshComponent> GetMesh() const { return mesh; }

	//Setters
	FORCEINLINE UPROPERTY(BlueprintCallable) void SetChessPieceOnSquare(AChessPiece* _newPiece) { chessPieceOnSquare = _newPiece; }
	FORCEINLINE UPROPERTY(BlueprintCallable) void SetSquareType(TEnumAsByte<ESquareType> _squareType) { squareType = _squareType; }
	FORCEINLINE UPROPERTY(BlueprintCallable) void SetCoordinates(const FCoordinates& _coordinates) { coordinates = _coordinates; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void InitializeBoardOwner(TObjectPtr<AChessboard> _owner); //owner needs to be initialized before beginplay of this actor

};
