#pragma once
#include <stdio.h>
#include <stdarg.h>

/// @brief debug.logへprintf形式のログを書き込む
/// @param format printf形式の書式文字列
/// @param ... 書式に対応する可変引数
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

inline bool DebugOn = false; ///< trueのときだけデバッグ表示を行う