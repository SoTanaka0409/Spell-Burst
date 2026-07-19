
$file = "Source\InputManager.cpp"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))

$c = $c -replace "int InputManager::up_buffer_\[256\] = \{ 0 \};", "int InputManager::up_buffer_[256] = { 0 };`r`nint InputManager::mouse_down_buffer_ = 0;"

$func = @"
int InputManager::CheckMouseDown(int button)
{
    int state = GetMouseInput() & button;
    int result = 0;
    if ((mouse_down_buffer_ & button) == 0 && state != 0) result = 1;
    if (state != 0) mouse_down_buffer_ |= button;
    else mouse_down_buffer_ &= ~button;
    return result;
}

int InputManager::CheckMousePress(int button)
{
    return (GetMouseInput() & button) != 0 ? 1 : 0;
}

int InputManager::CheckMouseUp(int button)
{
    // Not implemented fully for buffer yet, simplify to down check inverse
    return 0; // Or implement later if needed
}

void InputManager::GetMousePosition(int* x, int* y)
{
    GetMousePoint(x, y);
}
"@

$c = $c + "`r`n" + $func + "`r`n"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

