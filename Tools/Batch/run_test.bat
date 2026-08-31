call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl test.cpp /I"C:\DxLib" /link /LIBPATH:"C:\DxLib"
.\test.exe
type test_out.txt
