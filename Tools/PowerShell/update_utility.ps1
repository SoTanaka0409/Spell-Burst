
$file = "Source\Utility.h"
$c = [System.IO.File]::ReadAllText($file, [System.Text.Encoding]::GetEncoding(932))
$homingFunc = "
	/*
	 * ホーミング（追尾）のための新しい進行方向を計算する。
	 * [入力] currentDir: 現在の進行方向, currentPos: 現在の座標, targetPos: 目標の座標, rotationSpeed: 回転速度(0.0~1.0)
	 * [出力] 新しい進行方向(正規化済み)
	 * [副作用] なし
	 */
	static Vector2 CalculateHomingDirection(Vector2 currentDir, Vector2 currentPos, Vector2 targetPos, float rotationSpeed)
	{
		Vector2 toTarget = (targetPos - currentPos).Normalized();
		Vector2 newDir = (currentDir * (1.0f - rotationSpeed) + toTarget * rotationSpeed);
		if (newDir.MagnitudeSq() > 0.0f)
		{
			return newDir.Normalized();
		}
		return currentDir;
	}
};"
$c = $c -replace "};\s*$", $homingFunc
[System.IO.File]::WriteAllText($file, $c, [System.Text.Encoding]::GetEncoding(932))

