// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChessMeshDataAsset.generated.h"

UENUM(BlueprintType)
enum ESquareType
{
	SquareNone,
	BorderSquare,
	CornerSquare,
	SIZE
};

UCLASS(Blueprintable, BlueprintType)
class CHESSPROJECT_API UChessMeshDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere) TMap<TEnumAsByte<ESquareType>, TObjectPtr<UStaticMesh>> associationsSquareToMesh;

public:
	FORCEINLINE UPROPERTY(BlueprintCallable) TMap<TEnumAsByte<ESquareType>, TObjectPtr<UStaticMesh>> GetAssociationsSquareToMesh() const {
		return associationsSquareToMesh;
	};
	FORCEINLINE UPROPERTY(BlueprintCallable) TObjectPtr<UStaticMesh> GetMeshForSqauareType(const TEnumAsByte<ESquareType>& _enum) const
	{
		const TObjectPtr<UStaticMesh>* _toReturn = associationsSquareToMesh.Find(_enum);
		return _toReturn ? (*_toReturn) : nullptr;
	}

private:
	UFUNCTION(CallInEditor) void EmplaceBack();
};
