#include "QuizWidget.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Algo/RandomShuffle.h"
#include "QuizDescription.h"
#include "QuizTables.h"

// コンストラクタの実装
UQuizWidget::UQuizWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/**
 * クイズのカテゴリ数を取得する
 * @return カテゴリ数（int型）
 */
int32 UQuizWidget::GetQuizCategoryCount()
{
	// QuestionTablesが設定されているか確認
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return 0;
	}
	const int32 category_count = QuestionTables->GetRowNames().Num();
	return category_count;
}

/**
 * 指定インデックスのクイズカテゴリ名を取得する
 * @param Index 取得したいカテゴリのインデックス
 * @return カテゴリ名（FText型）
 */
FText UQuizWidget::GetQuizCategoryNames(const int32 Index)
{
	// QuestionTablesが設定されているか確認
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return FText();
	}

	const TArray<FName> RowNames = QuestionTables->GetRowNames();
	// 行数チェック
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in QuestionTables."));
		return FText();
	}
	// インデックス範囲チェック
	if (Index < 0 || Index >= RowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Index out of bounds for QuestionTables."));
		return FText();
	}

	// 指定されたインデックスの行名からカテゴリ名を取得
	FQuizTables* QuizTables = QuestionTables->FindRow<FQuizTables>(RowNames[Index], TEXT(""));
	if (!QuizTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionTables."));
		return FText();
	}
	return QuizTables->Category;
}

/**
 * 指定カテゴリのクイズデータをロードする
 * @param QuizType カテゴリインデックス
 */
void UQuizWidget::LoadQuizData(const int32 QuizType)
{
	// QuestionTablesが設定されているか確認
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return;
	}

	// DataTableの行名を取得
	TArray<FName> QuizTablesRowNames = QuestionTables->GetRowNames();
	// 行数チェック
	if (QuizTablesRowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in QuestionTables."));
		return;
	}
	// インデックス範囲チェック
	if (QuizType < 0 || QuizType >= QuizTablesRowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("QuizType index out of bounds."));
		return;
	}
	// 指定行からクイズテーブル情報を取得
	FQuizTables* QuizTables = QuestionTables->FindRow<FQuizTables>(QuizTablesRowNames[QuizType], TEXT(""));
	if (!QuizTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionTables."));
		return;
	}

	LoadedQuizData = nullptr;
	// クイズデータパスが有効な場合のみロード
	if (!QuizTables->QuizDataPath.IsNull())
	{
		LoadedQuizData = Cast<UDataTable>(
			StaticLoadObject(UDataTable::StaticClass(), nullptr, *QuizTables->QuizDataPath.ToString())
		);

		if (!LoadedQuizData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load DataTable from path: %s"), *QuizTables->QuizDataPath.ToString());
			return;
		}
	}
}

/**
 * クイズの問題と回答をランダムに抽選する
 * @param Question 問題文（出力）
 * @param Answer0~3 回答選択肢（出力）
 */
void UQuizWidget::LotteryQuiz(FText& Question, FText& Answer0, FText& Answer1, FText& Answer2, FText& Answer3)
{
	// クイズデータテーブルがロードされているか確認
	if (!LoadedQuizData)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadedQuizData is not set."));
		return;
	}

	// DataTableの行名を取得
	const TArray<FName> RowNames = LoadedQuizData->GetRowNames();
	// 行数チェック
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in LoadedQuizData."));
		return;
	}
	// ランダムに問題を抽選
	const int32 Lottery = FMath::RandRange(0, RowNames.Num() - 1);
	if (Lottery < 0 || Lottery >= RowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Lottery index out of bounds."));
		return;
	}
	// 抽選された行から問題データを取得
	FQuizDescription* TargetQuizDescription = LoadedQuizData->FindRow<FQuizDescription>(RowNames[Lottery], TEXT(""));
	if (!TargetQuizDescription)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionDataTable."));
		return;
	}

	// 回答の並び順を作成しシャッフル
	AnswerNumberArray = { 1,2,3,4 };
	Algo::RandomShuffle(AnswerNumberArray);
	// 正解番号をランダムに決定し、0をセット
	const int32 AnswerNumberIndex = FMath::RandRange(0, AnswerNumberArray.Num() - 1);
	AnswerNumberArray[AnswerNumberIndex] = 0;

	// 抽選結果の回答情報を取得するラムダ
	auto GetAnswer = [&TargetQuizDescription](int32 Number) {
		if (TargetQuizDescription == nullptr){
			return FText();
		}
		switch (Number) {
		case 0: return TargetQuizDescription->A0;
		case 1: return TargetQuizDescription->A1;
		case 2: return TargetQuizDescription->A2;
		case 3: return TargetQuizDescription->A3;
		case 4: return TargetQuizDescription->A4;
		}
		return FText();
	};

	// 問題文と回答選択肢をセット
	Question = TargetQuizDescription->Q;
	Answer0 = GetAnswer(AnswerNumberArray[0]);
	Answer1 = GetAnswer(AnswerNumberArray[1]);
	Answer2 = GetAnswer(AnswerNumberArray[2]);
	Answer3 = GetAnswer(AnswerNumberArray[3]);

	// 抽選結果をログ出力
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Q:%d A{ %d, %d, %d, %d }"), Lottery, AnswerNumberArray[0], AnswerNumberArray[1], AnswerNumberArray[2], AnswerNumberArray[3]), true, true, FLinearColor::Green, 2.0f);
}

/**
 * 指定番号が正解かどうかを判定する
 * @param Number 判定したい回答番号
 * @return 正解ならtrue、誤りならfalse
 */
bool UQuizWidget::IsLotteryJudgement(const int32 Number)
{
	// 範囲外アクセス防止
	if (Number < 0 || Number >= AnswerNumberArray.Num())
	{
		return false;
	}
	return AnswerNumberArray[Number] == 0; // 0番が正解
}