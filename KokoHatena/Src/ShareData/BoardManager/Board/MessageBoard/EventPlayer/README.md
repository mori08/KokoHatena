# EventPlayer について

App/asset/data/event/ にイベントを作成する

tableArrayで定義したイベント群のイベントを順に処理する。

# イベントの用途・記述

## object
オブジェクトの生成

```toml
[[Event]]
    event = "object"
    type = ""
    name = ""
    [Event.param]
```

- `type`
    - `String`
    - オブジェクトの型
    - `EventPlayer::setGenerateObjectMap` 関数を参照
- `name`
    - `String`
    - 作成するオブジェクトの名前
    - actイベントで使用する
- `param`
    - `TomlValue`
    - 生成時に使用するパラメータ
    - 各オブジェクトのコンストラクタを参照

## act
オブジェクトへの命令

```toml
[[Event]]
    event = "act"
    name = ""
    [Event.param]
```

- `name`
    - `String`
    - 指定するオブジェクトの名前
    - objectイベントで指定する
- `param`
    - `TomlValue`
    - 命令時に使用するパラメータ
    - 各オブジェクトの `receive` 関数を参照

## flag
jumpイベントで使用するフラグの更新

```toml
[[Event]]
    event = "jump"
    name = ""
    value = ""
```

- `name`
    - `String`
    - フラグ名
- `value`
    - `bool`
    - 更新する値
    - 未指定なら `false`

## jump
別イベント群へ遷移

```toml
[[Event]]
    event = "jump"
    to = ""
    flag = ""
```

- `to`
    - `String`
    - 遷移先のイベント群の名前
- `flag`
    - `String`
    - 参照するフラグの名前、フラグが `false` なら遷移しない
    - フラグが未指定なら、フラグを確認せず遷移

## board
他ボードへのリクエスト

```toml
[[Event]]
    event = "board"
    role = ""
    text = ""
```

- `role`
    - `String`
    - ボードの指定
    - BoardConst.hpp 参照
- `text`
    - `String`
    - ボードへ送る requestText

## scene
シーン遷移

```toml
[[Event]]
    event = "scene"
    scene = ""
```

- `scene`
    - `String`
    - Sceneの指定
    - SceneConfig.hpp 参照

## receive
`MessageBoard` に指定して `requestText` が送信されるまで待機

```toml
[[Event]]
    event = "receive"
    name = ""
```

- `name`
    - `String`
    - 待機する requestText

## wait
指定された時間待機

```toml
[[Event]]
    event = "wait"
    time = 0.0
```

- `time`
    - `double`
    - 待機する時間(s)
