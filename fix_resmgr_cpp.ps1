$file = 'Source\ResourceManager.cpp'
$content = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$content = $content -replace '\bgraphMap\b', 'graph_map_'
$content = $content -replace '\bfontMap\b', 'font_map_'
$content = $content -replace 'int ResourceManager::GetFont\(int size_, int thickness\)', 'int ResourceManager::GetFont(int size, int thickness)'
$content = $content -replace 'std::make_pair\(size_, thickness\)', 'std::make_pair(size, thickness)'
$content = $content -replace 'CreateFontToHandle\(NULL, size_, thickness, -1\)', 'CreateFontToHandle(NULL, size, thickness, -1)'

[System.IO.File]::WriteAllText($file, $content, [System.Text.Encoding]::GetEncoding(932))
