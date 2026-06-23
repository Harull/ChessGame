// Fill out your copyright notice in the Description page of Project Settings.


#include "Chessboard.h"
#include <ChessProject/ChessSquare/ChessSquare.h">
#include <ChessProject/Macro/Macro.h>

// Sets default values
AChessboard::AChessboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
}

void AChessboard::BeginPlay()
{
	Super::BeginPlay();

}

AChessSquare* AChessboard::GetSquareAtCoordinates(const int _x, const int _y)
{
	const int _indexToPick = _x + _y * sizeY;
	if (board.IsValidIndex(_indexToPick)) return GetChessSquareFromChildActorComponent(board[_indexToPick]);
	LOG_ERROR("Get square at coordinates is invalid index, returning nullptr");
	return nullptr;
}

void AChessboard::GetSquaresInDirection(AChessSquare* _squareFrom, const int _numberOfSquare, const int _directionBitmask, const int _blockingRuleBitmask)
{
	//TODO

}

void AChessboard::ClearBoard()
{
	for (auto& _chessSquare : board)
	{
		if (_chessSquare)
		{
			_chessSquare->UnregisterComponent();
			_chessSquare->DestroyComponent();
		}
	}
	board.Empty();
}

void AChessboard::InitializeVisualBoard()
{
	//ApplyMeshesToGivenChessSquare();
	PlaceChessSquares();
	PlaceChessBorders();
}

//void AChessboard::ApplyMeshesToGivenChessSquare()
//{
//	if (!chessMeshDataAsset) {
//		LOG_ERROR("No chessMeshDataAsset referenced in Chessboard, returning...");
//		return;
//	}
//
//	for (auto& _childActor : board)
//	{
//		TObjectPtr<AChessSquare> _chessSquare = GetChessSquareFromChildActorComponent(_childActor);
//		if (!_chessSquare)continue;
//		if (TObjectPtr<UStaticMeshComponent> _mesh = _chessSquare->GetMesh())
//			_mesh->SetStaticMesh(chessMeshDataAsset->GetMeshForSqauareType(_chessSquare->GetSquareType()));
//	}
//}

void AChessboard::PlaceChessSquares()
{
	//First define the max height and the max with of our chess square meshes 
	ComputeMaxBounds();

	//Compute the global offset per chess square, in order to center the board to it's actor location
	const FVector& _offset = FVector(maxSquareHeight * sizeX / 2, maxSquareWidth * sizeY / 2, 0) -
		FVector(maxSquareHeight / 2, maxSquareWidth / 2, 0);
	
	//Actually place chess squares in the world
	for (size_t _i = 0; _i < sizeX; _i++)
	{
		for (size_t _j = 0; _j < sizeY; _j++)
		{
			TObjectPtr<UChildActorComponent> _chessSquare = board[_i * sizeX + _j];
			if (!_chessSquare)continue;
			_chessSquare->SetRelativeLocation(FVector(maxSquareHeight * _i, maxSquareWidth * _j, 0) - _offset);
			_chessSquare->SetRelativeRotation(FQuat::Identity);
			_chessSquare->SetRelativeScale3D(FVector::OneVector);
		}
	}
}

void AChessboard::ComputeMaxBounds()
{
	maxSquareHeight = -1;
	maxSquareWidth = -1;

	for (size_t _i = 0; _i < sizeX; _i++)
	{
		for (size_t _j = 0; _j < sizeY; _j++)
		{
			TObjectPtr<AChessSquare> _chessSquare = GetChessSquareFromChildActorComponent(board[_i * sizeX + _j]);
			if (!_chessSquare)continue;
			if (!_chessSquare)continue;
			if (TObjectPtr<UStaticMeshComponent> _mesh = _chessSquare->GetMesh())
			{
				const FVector& _boxExtent = _mesh->GetStaticMesh()->GetBounds().BoxExtent * 2;
				const FVector& _componentScale = _mesh->GetComponentScale();
				maxSquareHeight = FMath::Max(maxSquareHeight, _boxExtent.X * _componentScale.X);
				maxSquareWidth = FMath::Max(maxSquareWidth, _boxExtent.Y * _componentScale.Y);
			}
		}
	}
}



void AChessboard::PlaceChessBorders()
{
	
}

TObjectPtr<UChildActorComponent> AChessboard::CreateChildrenChessSquare(TSubclassOf<AChessSquare>& _toSpawn)
{
	if (!_toSpawn)return nullptr;
	UChildActorComponent* _newComp = NewObject<UChildActorComponent>(this);
	//_newComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	_newComp->CreationMethod = EComponentCreationMethod::Instance;
	_newComp->SetMobility(EComponentMobility::Movable);
	_newComp->bEditableWhenInherited = true;
	_newComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	_newComp->RegisterComponent();
	_newComp->SetChildActorClass(_toSpawn);
	_newComp->CreateChildActor();
	return _newComp;
}

TObjectPtr<AChessSquare> AChessboard::GetChessSquareFromChildActorComponent(TObjectPtr<UChildActorComponent> _childActor)
{
	if (!_childActor) return nullptr;
	return Cast<AChessSquare>(_childActor->GetChildActor());
}

