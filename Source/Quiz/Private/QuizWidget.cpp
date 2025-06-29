#include "QuizWidget.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Algo/RandomShuffle.h"
#include "QuizDescription.h"
#include "QuizTables.h"

// �R���X�g���N�^�̎���
UQuizWidget::UQuizWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/**
 * �N�C�Y�̃J�e�S�������擾����
 * @return �J�e�S�����iint�^�j
 */
int32 UQuizWidget::GetQuizCategoryCount()
{
	// QuestionTables���ݒ肳��Ă��邩�m�F
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return 0;
	}
	const int32 category_count = QuestionTables->GetRowNames().Num();
	return category_count;
}

/**
 * �w��C���f�b�N�X�̃N�C�Y�J�e�S�������擾����
 * @param Index �擾�������J�e�S���̃C���f�b�N�X
 * @return �J�e�S�����iFText�^�j
 */
FText UQuizWidget::GetQuizCategoryNames(const int32 Index)
{
	// QuestionTables���ݒ肳��Ă��邩�m�F
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return FText();
	}

	const TArray<FName> RowNames = QuestionTables->GetRowNames();
	// �s���`�F�b�N
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in QuestionTables."));
		return FText();
	}
	// �C���f�b�N�X�͈̓`�F�b�N
	if (Index < 0 || Index >= RowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Index out of bounds for QuestionTables."));
		return FText();
	}

	// �w�肳�ꂽ�C���f�b�N�X�̍s������J�e�S�������擾
	FQuizTables* QuizTables = QuestionTables->FindRow<FQuizTables>(RowNames[Index], TEXT(""));
	if (!QuizTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionTables."));
		return FText();
	}
	return QuizTables->Category;
}

/**
 * �w��J�e�S���̃N�C�Y�f�[�^�����[�h����
 * @param QuizType �J�e�S���C���f�b�N�X
 */
void UQuizWidget::LoadQuizData(const int32 QuizType)
{
	// QuestionTables���ݒ肳��Ă��邩�m�F
	if (!QuestionTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestionTables is not set."));
		return;
	}

	// DataTable�̍s�����擾
	TArray<FName> QuizTablesRowNames = QuestionTables->GetRowNames();
	// �s���`�F�b�N
	if (QuizTablesRowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in QuestionTables."));
		return;
	}
	// �C���f�b�N�X�͈̓`�F�b�N
	if (QuizType < 0 || QuizType >= QuizTablesRowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("QuizType index out of bounds."));
		return;
	}
	// �w��s����N�C�Y�e�[�u�������擾
	FQuizTables* QuizTables = QuestionTables->FindRow<FQuizTables>(QuizTablesRowNames[QuizType], TEXT(""));
	if (!QuizTables)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionTables."));
		return;
	}

	LoadedQuizData = nullptr;
	// �N�C�Y�f�[�^�p�X���L���ȏꍇ�̂݃��[�h
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
 * �N�C�Y�̖��Ɖ񓚂������_���ɒ��I����
 * @param Question ��蕶�i�o�́j
 * @param Answer0~3 �񓚑I�����i�o�́j
 */
void UQuizWidget::LotteryQuiz(FText& Question, FText& Answer0, FText& Answer1, FText& Answer2, FText& Answer3)
{
	// �N�C�Y�f�[�^�e�[�u�������[�h����Ă��邩�m�F
	if (!LoadedQuizData)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadedQuizData is not set."));
		return;
	}

	// DataTable�̍s�����擾
	const TArray<FName> RowNames = LoadedQuizData->GetRowNames();
	// �s���`�F�b�N
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in LoadedQuizData."));
		return;
	}
	// �����_���ɖ��𒊑I
	const int32 Lottery = FMath::RandRange(0, RowNames.Num() - 1);
	if (Lottery < 0 || Lottery >= RowNames.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Lottery index out of bounds."));
		return;
	}
	// ���I���ꂽ�s������f�[�^���擾
	FQuizDescription* TargetQuizDescription = LoadedQuizData->FindRow<FQuizDescription>(RowNames[Lottery], TEXT(""));
	if (!TargetQuizDescription)
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in QuestionDataTable."));
		return;
	}

	// �񓚂̕��я����쐬���V���b�t��
	AnswerNumberArray = { 1,2,3,4 };
	Algo::RandomShuffle(AnswerNumberArray);
	// ����ԍ��������_���Ɍ��肵�A0���Z�b�g
	const int32 AnswerNumberIndex = FMath::RandRange(0, AnswerNumberArray.Num() - 1);
	AnswerNumberArray[AnswerNumberIndex] = 0;

	// ���I���ʂ̉񓚏����擾���郉���_
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

	// ��蕶�Ɖ񓚑I�������Z�b�g
	Question = TargetQuizDescription->Q;
	Answer0 = GetAnswer(AnswerNumberArray[0]);
	Answer1 = GetAnswer(AnswerNumberArray[1]);
	Answer2 = GetAnswer(AnswerNumberArray[2]);
	Answer3 = GetAnswer(AnswerNumberArray[3]);

	// ���I���ʂ����O�o��
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Q:%d A{ %d, %d, %d, %d }"), Lottery, AnswerNumberArray[0], AnswerNumberArray[1], AnswerNumberArray[2], AnswerNumberArray[3]), true, true, FLinearColor::Green, 2.0f);
}

/**
 * �w��ԍ����������ǂ����𔻒肷��
 * @param Number ���肵�����񓚔ԍ�
 * @return �����Ȃ�true�A���Ȃ�false
 */
bool UQuizWidget::IsLotteryJudgement(const int32 Number)
{
	// �͈͊O�A�N�Z�X�h�~
	if (Number < 0 || Number >= AnswerNumberArray.Num())
	{
		return false;
	}
	return AnswerNumberArray[Number] == 0; // 0�Ԃ�����
}