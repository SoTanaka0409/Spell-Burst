#include "Vector2.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <vector>
#include <fstream>
#include <algorithm>

// ゲーム全体で共通して使用する定数、数式、ランキングIO関数を定義するユーティリティクラス
class Utility
{
public:
	static const int kScreenWidth = 1600; 
	static const int kScreenHeight = 900; 

	static Vector2 stage_size_;
	static float time_scale_;

	/*
	 * 度数法の角度を弧度法（ラジアン）に変換する。
	 * [入力] deg: 度数法による角度
	 * [出力] 弧度法による角度（ラジアン）
	 * [副作用] なし
	 */
	static float DegToRad(float deg)
	{
		return deg * DX_PI_F / 180.0f;
	}

	/*
	 * ランキングデータを読み込み、昇順にソートする。
	 * [入力] outTimes: ランキングデータを格納する動的配列
	 * [出力] なし
	 * [副作用] ranking.txt からスコアを読み込み、昇順ソートして配列に格納する
	 */
	static void LoadTimeRanking(std::vector<int>& outTimes)
	{
		outTimes.clear();
		std::ifstream ifs("ranking.txt");
		if (ifs.is_open())
		{
			int t;
			while (ifs >> t)
			{
				outTimes.push_back(t);
			}
			ifs.close();
		}
		std::sort(outTimes.begin(), outTimes.end());
	}

	/*
	 * クリアタイムを保存し、上位5つの記録を更新する。
	 * [入力] timeMs: 保存するクリアタイム（ミリ秒）
	 * [出力] なし
	 * [副作用] ranking.txt に上位5つの記録を昇順ソートして書き込む
	 */
	static void SaveTimeRanking(int timeMs)
	{
		std::vector<int> times;
		LoadTimeRanking(times);
		times.push_back(timeMs);
		std::sort(times.begin(), times.end());
		
		std::ofstream ofs("ranking.txt", std::ios::trunc);
		if (ofs.is_open())
		{
			int count = (times.size() < 5) ? static_cast<int>(times.size()) : 5;
			for (int i = 0; i < count; ++i)
			{
				ofs << times[i] << "\n";
			}
			ofs.close();
		}
	}
};
