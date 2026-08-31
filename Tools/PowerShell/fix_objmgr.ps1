
$file = "Source\ObjectManager.h"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))

$func = @"
template<typename T, typename... Args>
std::weak_ptr<T> ObjectManager::Instantiate(Args&&... args)
{
    auto obj = std::make_shared<T>(std::forward<Args>(args)...);
    Master::sceneManager->GetCurrentScene()->GetObjectManager()->AddObject(obj);
    return obj;
}
"@

# Remove the func from before the class
$c = $c -replace "(?s)template<typename T, typename\.\.\. Args>\s*std::weak_ptr<T> ObjectManager::Instantiate\(Args&&.*?\}", ""

# Append it at the end
$c = $c + "`r`n" + $func + "`r`n"

[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

