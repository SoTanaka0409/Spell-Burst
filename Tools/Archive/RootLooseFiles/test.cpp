#include "DxLib.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) return -1;
    int h = LoadGraph("Resource/background.png");
    printf("Graph Handle: %d\n", h);
    FILE* f;
    fopen_s(&f, "test_out.txt", "w");
    fprintf(f, "Graph Handle: %d\n", h);
    fclose(f);
    DxLib_End();
    return 0;
}
