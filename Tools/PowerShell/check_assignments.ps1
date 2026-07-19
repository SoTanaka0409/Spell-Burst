$files = Get-ChildItem -Path Source -Include *.cpp, *.h -Recurse
foreach ($file in $files) {
    $lines = [System.IO.File]::ReadAllLines($file.FullName, [System.Text.Encoding]::GetEncoding(932))
    for ($i = 0; $i -lt $lines.Length; $i++) {
        $line = $lines[$i]
        
        # Check for member initialized with itself in initializer list: e.g. name_(name_)
        if ($line -match '([a-zA-Z0-9_]+_?)\(\1\)') {
            Write-Host ("[{0}:{1}] Initializer self-assignment: {2}" -f $file.Name, ($i+1), $line.Trim())
        }
        
        # Check for this->name_ = name_; or name_ = name_;
        # But name_ = name_ is caught if it's the exact same string
        if ($line -match '(this->)?([a-zA-Z0-9_]+_?)\s*=\s*\2\s*;') {
            Write-Host ("[{0}:{1}] Body self-assignment: {2}" -f $file.Name, ($i+1), $line.Trim())
        }
    }
}
