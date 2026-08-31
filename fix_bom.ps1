$bytes = [System.IO.File]::ReadAllBytes("Source\Boss.cpp")
$bom = [byte[]](239, 187, 191)
if ($bytes.Length -lt 3 -or $bytes[0] -ne 239 -or $bytes[1] -ne 187 -or $bytes[2] -ne 191) {
    [System.IO.File]::WriteAllBytes("Source\Boss.cpp", $bom + $bytes)
}
