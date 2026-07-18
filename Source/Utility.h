#include "Vector2.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX // Windows.hのmin/maxマクロ衝突を避ける
#endif
#include "DxLib.h"
#include <vector>
#include <fstream>
#include <algorithm>

class Utility
{
public:
    static const int kScreenWidth = 1600;  // 画面幅
    static const int kScreenHeight = 900;  // 画面高さ

    static Vector2 stage_size_;            // ステージ全体のサイズ
    static float time_scale_;              // ゲーム全体の時間倍率

    static float DegToRad(float deg)
    {
        return deg * DX_PI_F / 180.0f;
    }

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

    static Vector2 CalculateHomingDirection(Vector2 currentDir, Vector2 currentPos, Vector2 targetPos, float rotationSpeed)
    {
        Vector2 toTarget = (targetPos - currentPos).Normalized();
        Vector2 newDir = (currentDir * (1.0f - rotationSpeed) + toTarget * rotationSpeed);
        if (newDir.MagnitudeSq() > 0.0f)
        {
            return newDir.Normalized();
        }
        return currentDir;
    }
};