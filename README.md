# PiscineBSQwithCpp🍖

42Tokyoの入学試験「Piscine」の最終問題である「BSQ」をC++でやってみました。

## 本来の課題要件
- プログラムの名前: bsq
- 提出するファイル : Makefile、それ以外の必要なファイル
- 使用可能な関数 : open, close, read, write, malloc, free, exit
- 入力: 図が記入されているファイル 
- 説明: 与えられた図の中で、面積が最大の正方形を描け

### 以下問題文
- この課題の目的は、マップ上で最大の正方形を見つけ、障害物を回避することである。
- マップの情報が入ったファイルが提供され、それがプログラムのコマンドライン引数として渡されなければならない。
- マップの最初の行には、マップに関する以下の情報が記載されている。
    - マップ上の行数
    - “empty”の文字
    - “obstacle”の文字 
    - “full”の文字
- マップは、“empty”文字、行、“obstacle”文字で構成されている。
- プログラムの目的は、“empty”文字を“full”文字に置き換え、可能な限り最大の正方形を描くことである。
- 複数の解が存在する場合は、マップの一番上に最も近い正方形を描き、その次にマップの左に最も近い正方形を描くこと。
- プログラムは、1〜n個のファイルを引数として処理すること。
- プログラムが複数のマップをコマンドライン引数から受け取る場合は、それぞれの解、または、map errorの後に改行すること。
- コマンドライン引数がない場合は、プログラムは標準入力から読み取るこ
と。
- プロジェクトをコンパイルするための有効なMakefileが必要である。
Makefileは、relinkしないこと。
- 有効なマップの定義：
    - すべての行は、同じ長さであること。
    - 1つのボックスの行が、少なくとも1つ存在すること。 
    - 行末に改行があること。
    - マップ上の文字は、最初の行で指定された文字のみであること。
    - 最初の行に文字がない場合、または、2つの文字（empty, full, obstacle）が 同一の場合、マップは無効である。
    - 文字には、表示可能な任意の文字、数字を使用できる。
    - 無効なマップである場合、プログラムは標準エラー出力に改行が続くmap errorを出力すること。その後、プログラムは次のマップに進む。
- 動作例
```bash
%>cat example_file
9.ox
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
%>
```

```bash
%>./bsq example_file
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx...o...........
.....xxxxxxx...............
......o..............o.....
..o.......
%>
```

- 表示の都合上、正方形に見えないが、正方形である。

## 問題の要約
この課題は、与えられたマップ上で障害物を避けながら、空きセルのみで構成される最大の正方形を描くプログラムを作成するものです。<br>
入力ファイルは以下の形式になっています:

```bash
username@ % ./bsq map/map.txt
```

- マップは5行あり、空きセルは .、障害物はo、最大正方形部分はxに置き換えられる。
- マップの各行は同じ長さで、使用される文字はヘッダーで指定されたempty文字とobstacle文字のみです。
- プログラムは、空きセルだけで構成される最大の正方形を探索し、その領域をfull文字 に置き換えて出力します。<br>
もし複数候補がある場合は、最も上かつ左側に位置する正方形を選びます。

## 問題の解答の流れ
1. 入力を読み込み、最初のヘッダー行から行数と使用する文字empty,obstacle,full）を取得。
2. マップ本体の各行が同一の長さであること、使用される文字が正しいことをチェック。
3. 入力が不正な場合は、標準エラー出力にmap errorを出力する。
4. マップ上の各セル (i, j) について、そこを右下端とする正方形の最大の辺の長さを DP配列で計算します。
5. セルがobstacleならdp[i][j]は0、emptyなら上、左、左上の最小値に1を加えた値を設定する。
6. この過程で、全セルを一度走査するだけで最大の正方形のサイズと、その左上座標が求められる。
7. 求めた最大正方形の位置とサイズを元に、該当する領域内のempty文字をfull文字に置き換える。
8. 更新されたマップを出力する。

## 使用したアルゴリズム「動的計画法」について
動的計画法は問題を部分問題に分割し、各部分問題の解を再利用することで全体の解を効率的に求めるアルゴリズムです。

- DP配列の定義
    - 各セルdp[i][j]は、元のマップ上のセル(i, j)を右下端とする正方形の最大の辺の長さを表す。
- 漸化式
    - 空きセルの場合:
    ```bash
    dp[i][j] = min( dp[i-1][j], dp[i][j-1], dp[i-1][j-1] ) + 1
    ```
    上、左、左上のセルの最小値に1を加えることで、そこまで拡大できる正方形の最大のサイズが求められる。
    - 障害物の場合:
    ```bash
    dp[i][j] = 0
    ```
    障害物があるセルは正方形の一部に含められないため、サイズは0となります。

- このアルゴリズムのメリット
    - この手法では、各セルの計算を一度だけ行うため、全体の計算量は O(n*m) に抑えられ、大きなマップでも高速に最大正方形を見つけることが可能です。