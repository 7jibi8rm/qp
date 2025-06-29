// QuizWidget.h - �N�C�YUI�E�B�W�F�b�g�̒�`

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "QuizDescription.h"

#include "QuizWidget.generated.h"

/**
 * UQuizWidget�N���X�́A�N�C�Y��ʂ�UI���W�b�N���Ǘ����܂��B
 * �N�C�Y�̃J�e�S���擾�A���f�[�^�̃��[�h�A�����_�����I�A�񓚔���Ȃ�
 * �N�C�Y�@�\�̒��S�I�Ȗ�����S���܂��B
 */
UCLASS()
class QUIZ_API UQuizWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 * �R���X�g���N�^
	 * @param ObjectInitializer UE�̃I�u�W�F�N�g�������p
	 */
	UQuizWidget(const FObjectInitializer& ObjectInitializer);

	/**
	 * �N�C�Y�̃J�e�S�������擾���܂��B
	 * @return �J�e�S�����iint�^�j
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	int32 GetQuizCategoryCount();

	/**
	 * �w��C���f�b�N�X�̃N�C�Y�J�e�S�������擾���܂��B
	 * @param Index �擾�������J�e�S���̃C���f�b�N�X
	 * @return �J�e�S�����iFText�^�j
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	FText GetQuizCategoryNames(const int32 Index);

	/**
	 * �w��J�e�S���̃N�C�Y�f�[�^�����[�h���܂��B
	 * @param QuizType �J�e�S���C���f�b�N�X
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	void LoadQuizData(const int32 QuizType);

	/**
	 * �N�C�Y�̖��Ɖ񓚂������_���ɒ��I���܂��B
	 * @param Question ��蕶�i�o�́j
	 * @param Answer0~3 �񓚑I�����i�o�́j
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	void LotteryQuiz(FText& Question, FText& Answer0, FText& Answer1, FText& Answer2, FText& Answer3);

	/**
	 * �w��ԍ����������ǂ����𔻒肵�܂��B
	 * @param Number ���肵�����񓚔ԍ�
	 * @return �����Ȃ�true�A���Ȃ�false
	 */
	UFUNCTION(BlueprintCallable, Category = "Quiz")
	bool IsLotteryJudgement(const int32 Number);

	/**
	 * �N�C�Y�J�e�S�������i�[�����f�[�^�e�[�u��
	 * �G�f�B�^��Blueprint����ݒ�\
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiz")
	UDataTable* QuestionTables;

private:

	/**
	 * ���݃��[�h���̃N�C�Y���f�[�^�e�[�u��
	 */
	UDataTable* LoadedQuizData{ nullptr };

	/**
	 * �񓚑I�����̕��я���ێ�����z��
	 * ���I���ɃV���b�t������A�����ʒu���Ǘ�
	 */
	TArray<int32> AnswerNumberArray{};
};