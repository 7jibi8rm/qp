// QuizDescription.h - �N�C�Y���f�[�^�\���̂̒�`

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "QuizDescription.generated.h"

/**
 * FQuizDescription�́A1�╪�̃N�C�Y�f�[�^��\���\���̂ł��B
 * ��蕶�ƕ����̉񓚑I�������i�[���ADataTable�ŗ��p����܂��B
 */
USTRUCT(BlueprintType)
struct QUIZ_API FQuizDescription : public FTableRowBase
{
	GENERATED_BODY()

	/** ��蕶 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Q{};

	/** �񓚑I����0�i�ʏ�͐����j */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A0{};

	/** �񓚑I����1 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A1{};

	/** �񓚑I����2 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A2{};

	/** �񓚑I����3 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A3{};

	/** �񓚑I����4 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A4{};
};