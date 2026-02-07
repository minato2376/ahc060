# Heuristic Contest Workspace

C++23 (GCC 15.2.0) を使用したヒューリスティックコンテスト用ワークスペース。

## セットアップ

### Dev Container (推奨)

VS Code の Dev Containers 拡張機能を使用して開きます。GCC 15.2.0、clang-format、gdb などが自動でセットアップされます。

### サブモジュール

アルゴリズム・データ構造ライブラリ [library-cpp](https://github.com/minato2376/library-cpp) を git submodule として含みます。

```bash
git submodule update --init --recursive
```

## 使い方

### ビルド・実行

```bash
# コンパイル（デバッグ・サニタイザフラグ付き）
bin/cppx build A.cpp        # a.out を出力
bin/cppx build A.cpp -o A   # A を出力

# 実行
bin/cppx run            # ./a.out を実行
bin/cppx run ./A        # ./A を実行
```

### 提出用バンドル

`library-cpp` の `#include` を展開して単一ファイルにまとめます。

```bash
bin/cppx bundle A.cpp
```

### フォーマット

```bash
bin/cppx format A.cpp
```

### ツール

```bash
# zipファイルをプロジェクトルートに展開（テストケース・ツール等）
bin/tools unzip testcases.zip
```

## プロジェクト構成

```
.
├── A.cpp                 # ソリューションファイル
├── STATEMENT.md          # 問題文
├── library-cpp/          # アルゴリズム・データ構造ライブラリ (submodule)
├── bin/cppx              # ビルド・実行ラッパースクリプト
├── bin/tools             # ユーティリティツール
├── .devcontainer/        # Dev Container 設定
└── .clang-format         # コードフォーマット設定
```

## ライブラリの利用

ソリューションファイルからの相対パスでインクルードします。

```cpp
#include "library-cpp/datastructure/UnionFind.hpp"
#include "library-cpp/graph/Dijkstra.hpp"
```
