# Project Customizations

## Naming Conventions
- **Member Variables**: Snake case, suffixed with an underscore (snake_case_).
  - Example: speed_, hp_, is_visible_.
  - Discard Hungarian notation (e.g., mbIsVisible, mfScale).
- **Classes / Structs**: Pascal case (PascalCase).
  - Example: CowMove, Player3D, CharacterParams.
- **Functions / Methods**: Pascal case (PascalCase).
  - Example: SpawnCow(), MoveCharacter(), DrawBar().
- **Local Variables / Function Arguments**: Camel case (camelCase).
  - Example: ilename, initPos, scatterRadius.
- **Constants / Enums**: Pascal case, prefixed with 'k' (kPascalCase).
  - Example: kCowGold, kSceneGame, kFever.

## Commenting Rules
- **Function Documentation**:
  - Use block comments /* ... */.
  - Only for methods containing non-trivial logic (exclude simple getters/setters).
  - Must explicitly state the function's purpose and contain [入力], [出力], and [副作用].
  - Example:
    /*
     * 状態（フィーバー等）に応じた牛の出現制御を行う。
     * [入力] filename:モデルパス, pos:基準座標, scale:拡大率, tag:牛種類, count:生成個数, is_fever:フィーバー中か
     * [出力] なし
     * [副作用] 管理リストへ牛を追加、またはプールから復帰させる
     */
- **Inline Comments**:
  - Use line comments //.
  - Keep to a maximum of 3 lines per block.
  - Focus on *why* the code does what it does (e.g. bug prevention, performance reasons, significance).
