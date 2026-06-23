// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMeshDataAsset.h"
#include <ChessProject/Macro/Macro.h>

void UChessMeshDataAsset::EmplaceBack()
{
	const int32 _num = associationsSquareToMesh.Num();
	if (_num >= SIZE)
	{
		LOG_ERROR("Can't emplace back, all enums are already taken");
		return;
	}
	associationsSquareToMesh.Add(static_cast<ESquareType>(_num));
}
