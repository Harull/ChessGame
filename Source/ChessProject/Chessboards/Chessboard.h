// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ChessProject/DataAssets/ChessMeshDataAsset.h>
#include "Chessboard.generated.h"

class AChessSquare;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EDirectionBitmask : uint16
{
	DirectionNone       = 0b0 UMETA(Hidden),
	Horizontal			= 0b1,
	HorizontalRight		= 0b10,    
	HorizontalLeft		= 0b100,   
	Vertical			= 0b1000,
	VerticalUp			= 0b100000,
	VerticalDown		= 0b1000000,
	Diagonal			= 0b10000000,
	DiagonalRightSideUp = 0b100000000,
	DiagonalLeftSideUp	= 0b1000000000,
};

inline bool operator== (int _a, EDirectionBitmask _b)
{
	return _a == static_cast<uint8>(_b);
}
inline bool operator== (EDirectionBitmask _a, int _b)
{
	return static_cast<uint8>(_a) == _b;
}

ENUM_CLASS_FLAGS(EDirectionBitmask)


UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EBlockingRuleBitmask : uint8
{
	BlockingNone	= 0b0 UMETA(Hidden),
	IgnoreAll		= 0b1, //Ignoring will make it so the chess square is not a blocking hit, but not a valid square to go to
	IgnoreIfEnemy	= 0b10,    
	IgnoreIfAlly	= 0b100,    
	BlockAll		= 0b1000, //Blocking will mean it stops the patern in wich the piece is going
	BlockIfAlly		= 0b100000,
	BlockIfEnemy	= 0b1000000,
};
inline bool operator== (int _a, EBlockingRuleBitmask _b)
{
	return _a == static_cast<uint8>(_b);
}
inline bool operator== (EBlockingRuleBitmask _a, int _b)
{
	return static_cast<uint8>(_a) == _b;
}
ENUM_CLASS_FLAGS(EBlockingRuleBitmask)




UCLASS()
class CHESSPROJECT_API AChessboard : public AActor
{
	GENERATED_BODY()

protected:
	// Those child actor components classes should be TSubclassOf<AChessSquare>
	UPROPERTY(VisibleAnywhere, Category = "Components") TArray<TObjectPtr<UChildActorComponent>> board;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UChessMeshDataAsset> chessMeshDataAsset;

	UPROPERTY(VisibleAnywhere, Category = "Debug") TArray<TObjectPtr<UStaticMeshComponent>> borderOutOfBounds;
	UPROPERTY(VisibleAnywhere, Category = "Debug") int sizeX;
	UPROPERTY(VisibleAnywhere, Category = "Debug") int sizeY;

	float maxSquareHeight;
	float maxSquareWidth;

public:	
	AChessboard();

protected:
	virtual void BeginPlay() override;

public:
	/// @return The chess square at the given coordinates
	UFUNCTION(BlueprintCallable) AChessSquare* GetSquareAtCoordinates(const int _x, const int _y);

	/// <summary>
	/// Starting from the _squareFrom, towards the direction mask, blocking or not.
	/// </summary>
	/// <param name="_squareFrom"> The square to search from </param>
	/// <param name="_numberOfSquare"> The number of square to search in that direction </param>
	/// <param name="_directionBitmask"> The detailed direction to take as flag, see the enum EDirectionBitmask </param>
	/// <param name="_blockingRuleBitmask"> The blocking rule, see the enum EBlockingRuleBitmask </param>
	UFUNCTION(BlueprintCallable) void GetSquaresInDirection(AChessSquare* _squareFrom, const int _numberOfSquare, const int _directionBitmask = 0, const int _blockingRuleBitmask = 0);
	
	/// <summary>
	/// Method called in editor, it is used to generate a chess board.
	/// Members parameters int sizeX, sizeY; should always be initialized in there.
	/// </summary>
	UFUNCTION(CallInEditor) virtual void GenerateBoard() PURE_VIRTUAL(AChessboard::GenerateBoard, );
	UFUNCTION(CallInEditor) void ClearBoard();

protected:
	
	
	void InitializeVisualBoard();
	
	/// <summary>
	/// Give chess square their actual mesh
	/// </summary>
	//void ApplyMeshesToGivenChessSquare();

	/// <summary>
	/// Position the chess squares so it forms a board. Taking in account their bound
	/// </summary>
	void PlaceChessSquares();

	/// <summary>
	/// Compute the maxSquareHeight and maxSquareWidth member variables
	/// </summary>
	void ComputeMaxBounds();

	/// <summary>
	/// Place the border of the chessboard
	/// </summary>
	void PlaceChessBorders();

	/// <summary>
	/// Creates a child actor component based on the class referenced in parameter
	/// </summary>
	TObjectPtr<UChildActorComponent> CreateChildrenChessSquare(TSubclassOf<AChessSquare>& _toSpawn);

	/// <summary>
	/// Safely get the chess square actor from the child actor component referenced in parameter
	/// </summary>
	TObjectPtr<AChessSquare> GetChessSquareFromChildActorComponent(TObjectPtr<UChildActorComponent> _childActor);
};
