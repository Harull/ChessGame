// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardSquared.h"
#include <ChessProject/ChessSquare/ChessSquare.h">


void AChessboardSquared::GenerateBoard()
{
	ClearBoard();

	sizeX = sizeY = chessboardSize;
	const int _totalChessboardSize = chessboardSize * chessboardSize;
	board.Reserve(_totalChessboardSize);

	FActorSpawnParameters _spawnParameters;
	_spawnParameters.bNoFail = true;

	bool _isWhiteSquare = true;
	for (size_t _i = 0; _i < _totalChessboardSize; _i++)
	{
		if (_i % chessboardSize != 0)
			_isWhiteSquare = !_isWhiteSquare;

		TObjectPtr<UChildActorComponent> _createdChessSquare;
		if (_isWhiteSquare && whiteSquare)
			_createdChessSquare = CreateChildrenChessSquare(whiteSquare);
		else if (!_isWhiteSquare && blackSquare)
			_createdChessSquare = CreateChildrenChessSquare(blackSquare);
		board.Add(_createdChessSquare);

		if (_createdChessSquare)
			if (TObjectPtr<AChessSquare> _chessSquare = Cast<AChessSquare>(_createdChessSquare->GetChildActor()))
				_chessSquare->SetCoordinates(FCoordinates(_i % 8, _i / 8));


	}

	InitializeVisualBoard();
}
