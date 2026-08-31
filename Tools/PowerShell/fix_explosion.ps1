$file = 'Source\ExplosionParticle.cpp'
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$c = $c -replace 'life_time_ = life_time_;', 'this->life_time_ = life_time_;'
$c = $c -replace 'max_life_ = life_time_;', 'this->max_life_ = life_time_;'
$c = $c -replace 'color_ = color_;', 'this->color_ = color_;'
$c = $c -replace 'size_ = size_;', 'this->size_ = size_;'
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))
