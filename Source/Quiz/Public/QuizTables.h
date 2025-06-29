// QuizTables.h - クイズカテゴリ情報のデータ構造体定義

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/SoftObjectPath.h"

#include "QuizTables.generated.h"

/**
 * FQuizTablesは、クイズのカテゴリ情報を管理する構造体です。
 * 各カテゴリ名と、そのカテゴリに対応するクイズデータテーブルのパスを保持します。
 * DataTableとして利用され、カテゴリ選択やクイズデータのロードに使用されます。
 */
USTRUCT(BlueprintType)
struct QUIZ_API FQuizTables : public FTableRowBase
{
	GENERATED_BODY()

	/** カテゴリ名（例：理科、算数、英語など） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Category{};

	/** このカテゴリに対応するクイズデータテーブルのパス（SoftObjectPath） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FSoftObjectPath QuizDataPath;
};