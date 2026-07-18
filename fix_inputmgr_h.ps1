
$file = "Source\InputManager.h"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))

$c = $c -replace "private:", "    static int CheckMouseDown(int button);`r`n    static int CheckMousePress(int button);`r`n    static int CheckMouseUp(int button);`r`n    static void GetMousePosition(int* x, int* y);`r`n`r`nprivate:`r`n    static int mouse_down_buffer_;"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

