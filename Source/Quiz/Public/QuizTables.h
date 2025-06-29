// QuizTables.h - �N�C�Y�J�e�S�����̃f�[�^�\���̒�`

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/SoftObjectPath.h"

#include "QuizTables.generated.h"

/**
 * FQuizTables�́A�N�C�Y�̃J�e�S�������Ǘ�����\���̂ł��B
 * �e�J�e�S�����ƁA���̃J�e�S���ɑΉ�����N�C�Y�f�[�^�e�[�u���̃p�X��ێ����܂��B
 * DataTable�Ƃ��ė��p����A�J�e�S���I����N�C�Y�f�[�^�̃��[�h�Ɏg�p����܂��B
 */
USTRUCT(BlueprintType)
struct QUIZ_API FQuizTables : public FTableRowBase
{
	GENERATED_BODY()

	/** �J�e�S�����i��F���ȁA�Z���A�p��Ȃǁj */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Category{};

	/** ���̃J�e�S���ɑΉ�����N�C�Y�f�[�^�e�[�u���̃p�X�iSoftObjectPath�j */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FSoftObjectPath QuizDataPath;
};