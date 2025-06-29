// QuizWidget.h - クイズUIウィジェットの定義

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "QuizDescription.h"

#include "QuizWidget.generated.h"

/**
 * UQuizWidgetクラスは、クイズ画面のUIロジックを管理します。
 * クイズのカテゴリ取得、問題データのロード、ランダム抽選、回答判定など
 * クイズ機能の中心的な役割を担います。
 */
UCLASS()
class QUIZ_API UQuizWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 * コンストラクタ
	 * @param ObjectInitializer UEのオブジェクト初期化用
	 */
	UQuizWidget(const FObjectInitializer& ObjectInitializer);

	/**
	 * クイズのカテゴリ数を取得します。
	 * @return カテゴリ数（int型）
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	int32 GetQuizCategoryCount();

	/**
	 * 指定インデックスのクイズカテゴリ名を取得します。
	 * @param Index 取得したいカテゴリのインデックス
	 * @return カテゴリ名（FText型）
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	FText GetQuizCategoryNames(const int32 Index);

	/**
	 * 指定カテゴリのクイズデータをロードします。
	 * @param QuizType カテゴリインデックス
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	void LoadQuizData(const int32 QuizType);

	/**
	 * クイズの問題と回答をランダムに抽選します。
	 * @param Question 問題文（出力）
	 * @param Answer0~3 回答選択肢（出力）
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	void LotteryQuiz(FText& Question, FText& Answer0, FText& Answer1, FText& Answer2, FText& Answer3);

	/**
	 * 指定番号が正解かどうかを判定します。
	 * @param Number 判定したい回答番号
	 * @return 正解ならtrue、誤りならfalse
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	bool IsLotteryJudgement(const int32 Number);

	/**
	 * クイズカテゴリ情報を格納したデータテーブル
	 * エディタやBlueprintから設定可能
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz")
	UDataTable* QuestionTables;

private:

	/**
	 * 現在ロード中のクイズ問題データテーブル
	 */
	UDataTable* LoadedQuizData{ nullptr };

	/**
	 * 回答選択肢の並び順を保持する配列
	 * 抽選時にシャッフルされ、正解位置も管理
	 */
	TArray<int32> AnswerNumberArray{};
};