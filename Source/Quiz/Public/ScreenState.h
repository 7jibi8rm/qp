// ScreenState.h - 画面状態を表す列挙型の定義

#pragma once

#include "CoreMinimal.h"
#include "ScreenState.generated.h"

/**
 * ECPPScreenStateは、QuizGameの各画面状態を表す列挙型です。
 * ゲームの進行状況やUIの切り替えに利用します。
 */
UENUM(BlueprintType)
enum class ECPPScreenState : uint8
{
    /** タイトル画面 */
    Title = 0   UMETA(DisplayName = "Title"),
    /** メイン（クイズ出題）画面 */
    Main = 1    UMETA(DisplayName = "Main"),
    /** 正解時の画面 */
    Right = 2   UMETA(DisplayName = "Right"),
    /** 不正解時の画面 */
    Wrong = 3   UMETA(DisplayName = "Wrong"),
    /** タイムアップ時の画面 */
    Timeup = 4  UMETA(DisplayName = "Timeup"),
    /** 全問正解・クリア時の画面 */
    Clear = 5   UMETA(DisplayName = "Clear"),
};