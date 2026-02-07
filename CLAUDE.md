## 概要

C++23（GCC 15.2.0）を使用したヒューリスティックコンテスト用ワークスペース。再利用可能なアルゴリズム・データ構造ライブラリ（`library-cpp` git submodule、https://github.com/minato2376/library-cpp）を含みます。

## 問題文

@STATEMENT.md に記載。

## ビルド・実行

```bash
# ソリューションのコンパイル（cppx ラッパーによりデバッグ・サニタイザフラグ付き）
bin/cppx build A.cpp        # a.out を出力
bin/cppx build A.cpp -o A   # A を出力

# 提出用にインクルードを展開（library-cpp の #include を展開）
bin/cppx bundle A.cpp

# 実行（cppx 経由）
bin/cppx run            # ./a.out を実行
bin/cppx run ./A        # ./A を実行
```

## コードフォーマット

clang-format（Chromium ベーススタイル、インデント4スペース）。Dev Container では保存時に自動フォーマットが有効。設定は `.clang-format`。

```bash
# cppx 経由でソースファイルをフォーマット
bin/cppx format A.cpp
```

## アーキテクチャ

- **`A.cpp`** — ソリューションファイルのテンプレート。`library-cpp/other/template.hpp` をインクルードし、`solve()` 関数を定義する。

## 規約

- ライブラリヘッダは `.hpp` で、ソリューションファイルからの相対パスでインクルードする（例: `#include "library-cpp/datastructure/UnionFind.hpp"`）。
- テンプレートは `using namespace std;` を使用し、省略マクロを提供する — 既存のスタイルに従うこと。
- デバッグ出力は `#ifdef MINATO_LOCAL` ガードを使用する。`dbg()` マクロは stderr に出力する。
