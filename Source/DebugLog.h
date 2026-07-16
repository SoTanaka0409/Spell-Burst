#pragma once
#include <stdio.h>
#include <stdarg.h>

// 入力：format = printf形式の書式指定文字列, ... = 可変長引数
// 出力：なし
// 副作用：debug.logファイルへのログテキストの追記（アペンド）
// 設計ルール：ゲームが途中で強制終了（クラッシュ）した場合も、直前までのログが確実にディスクに残るよう毎回クローズする設計
inline void DebugLog(const char* format, ...)
{
	FILE* fp = nullptr;
	fopen_s(&fp, "debug.log", "a");
	if (fp)
	{
		va_list args;
		va_start(args, format);
		vfprintf(fp, format, args);
		va_end(args);
		fclose(fp);
	}
}

// 構成ルール：ヘッダーファイルを複数のソースで include した際に、リンク時の多重定義エラー（LNK2005）が発生するのを防ぐインライングローバル変数
inline bool DebugOn = false; // trueの時のみ、パフォーマンス統計やコリジョンボックスなどのデバッグ用情報を画面にオーバーレイ描画する