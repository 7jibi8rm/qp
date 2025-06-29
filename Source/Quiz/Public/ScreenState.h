// ScreenState.h - ��ʏ�Ԃ�\���񋓌^�̒�`

#pragma once

#include "CoreMinimal.h"
#include "ScreenState.generated.h"

/**
 * ECPPScreenState�́AQuizGame�̊e��ʏ�Ԃ�\���񋓌^�ł��B
 * �Q�[���̐i�s�󋵂�UI�̐؂�ւ��ɗ��p���܂��B
 */
UENUM(BlueprintType)
enum class ECPPScreenState : uint8
{
    /** �^�C�g����� */
    Title = 0   UMETA(DisplayName = "Title"),
    /** ���C���i�N�C�Y�o��j��� */
    Main = 1    UMETA(DisplayName = "Main"),
    /** �������̉�� */
    Right = 2   UMETA(DisplayName = "Right"),
    /** �s�������̉�� */
    Wrong = 3   UMETA(DisplayName = "Wrong"),
    /** �^�C���A�b�v���̉�� */
    Timeup = 4  UMETA(DisplayName = "Timeup"),
    /** �S�␳���E�N���A���̉�� */
    Clear = 5   UMETA(DisplayName = "Clear"),
};