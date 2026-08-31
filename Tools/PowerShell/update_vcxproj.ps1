
$file = "Project1.vcxproj"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding("utf-8"))

# Insert ClCompile
$c = $c -replace "<ClCompile Include=`"Source\\Bullet.cpp`" />", "<ClCompile Include=`"Source\Bullet.cpp`" />`r`n    <ClCompile Include=`"Source\BulletFactory.cpp`" />`r`n    <ClCompile Include=`"Source\EffectManager.cpp`" />"

# Insert ClInclude
$c = $c -replace "<ClInclude Include=`"Source\\Bullet.h`" />", "<ClInclude Include=`"Source\Bullet.h`" />`r`n    <ClInclude Include=`"Source\BulletFactory.h`" />`r`n    <ClInclude Include=`"Source\EffectManager.h`" />"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding("utf-8"))

