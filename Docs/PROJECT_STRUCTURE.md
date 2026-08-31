# Project Structure

このプロジェクトの主なフォルダ構成です。

- `Source/`: ゲーム本体のC++ソースコード。
- `Resource/assets.csv`: ゲーム内で使用する素材IDとファイルパスの対応表。
- `Resource/Runtime/`: 実行時に読み込む画像、3Dモデル、動画、音声素材。
- `Resource/SourceAssets/`: アニメーション素材など、制作・編集元として使う素材。
- `Docs/`: 作業メモやコメント移行時の資料。
- `Logs/`: 実行ログや調査用ログ。
- `Tools/`: 補助スクリプトや退避した検証用ファイル。

実行時に使う素材を追加・移動した場合は、`Resource/assets.csv` のパスも合わせて更新してください。
