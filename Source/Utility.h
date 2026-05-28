#pragma once
#include "DxLib.h"
#include <vector>
#include <fstream>
#include <algorithm>

//プログラム内で共通して使用する定数定義などをここに記述していく
//関数なども記述していく

class Utility
{
	public://定数定義
	static const int SCREEN_WIDTH = 1600; //画面の幅

	static const int SCREEN_HEIGHT = 900; //画面の高さ

	static VECTOR StageSize;
	static float TimeScale;



	static float DegToRad(float deg)
	{
		return deg * DX_PI_F / 180.0f;
	}

	static void LoadTimeRanking(std::vector<int>& outTimes) {
		outTimes.clear();
		std::ifstream ifs("ranking.txt");
		if (ifs.is_open()) {
			int t;
			while (ifs >> t) {
				outTimes.push_back(t);
			}
			ifs.close();
		}
		std::sort(outTimes.begin(), outTimes.end());
	}

	static void SaveTimeRanking(int timeMs) {
		std::vector<int> times;
		LoadTimeRanking(times);
		times.push_back(timeMs);
		std::sort(times.begin(), times.end());
		
		std::ofstream ofs("ranking.txt", std::ios::trunc);
		if (ofs.is_open()) {
			int count = (times.size() < 5) ? times.size() : 5;
			for (int i = 0; i < count; ++i) {
				ofs << times[i] << "\n";
			}
			ofs.close();
		}
	}


};
//