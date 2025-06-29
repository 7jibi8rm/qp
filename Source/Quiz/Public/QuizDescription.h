// QuizDescription.h - クイズ問題データ構造体の定義

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "QuizDescription.generated.h"

/**
 * FQuizDescriptionは、1問分のクイズデータを表す構造体です。
 * 問題文と複数の回答選択肢を格納し、DataTableで利用されます。
 */
USTRUCT(BlueprintType)
struct QUIZ_API FQuizDescription : public FTableRowBase
{
	GENERATED_BODY()

	/** 問題文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Q{};

	/** 回答選択肢0（通常は正解） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A0{};

	/** 回答選択肢1 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A1{};

	/** 回答選択肢2 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A2{};

	/** 回答選択肢3 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A3{};

	/** 回答選択肢4 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText A4{};
};