$file = 'Source\Object2D.h'
$lines = [System.IO.File]::ReadAllLines($file, [System.Text.Encoding]::GetEncoding(932))
$outLines = @()

foreach ($line in $lines) {
    if ($line -match '^\s*//.*蜈･.*') {
        continue
    }
    if ($line -match '^\s*//.*蜃ｺ.*') {
        continue
    }
    if ($line -match '^\s*//.*蜑ｯ.*') {
        continue
    }
    $outLines += $line
}

[System.IO.File]::WriteAllLines($file, $outLines, [System.Text.Encoding]::GetEncoding(932))
