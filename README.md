# libft

修正点があれば歓迎します。
ぜひ教えてください。

## 2025/7/10
理想的なft_get_next_line、strndupの追加

## 2025/7/17
absの追加

## 2025/7/20
ft_gnl: EOFに到達したとき、lineにメモリ確保しないように修正

## 2025/7/26
min, maxの追加

## 2025/8/5
ft_gnl: 最後の行に改行がないファイルを読み込めないバグを修正

## 2025/8/6
ft_gnl: get_line内、ft_strchr == NULL のときのエラーハンドリング修正

## 2025/9/8
ft_gnl: ft_get_next_lineの構造をシンプルにリファクタリング。

## 2025/9/9
もろもろのリファクタリング, ft_gnlのデバグ

## 2025/9/10
ft_isspace.cの追加

## 2025/9/28
ft_itoa.cのリファクタリング

## 2025/10/3
ft_lstシリーズのNULLカバーを除去。

## 2025/10/8
libft.hにft_strrchr()の追加。    

## 2025/10/10
ft_substr()で必要のない初期化を削除。   

## 2025/11/10
ft_atof()の追加

## 2025/11/11
ft_atof()の方針が定まらず。
こんがらがってきた。
`ft_atof`ディレクトリの追加。

## 2025/11/17
`ft_atof/ft_strtod.c`の追加。   
まだ、修正は必要。   

## 2025/11/18
`ft_atof/ft_strtod.c`の追加。   
`sun micro systems`から`glibc`を参考にという方針に変更。   
`ft_atof/ft_strtod`ヘルパー関数の追加、パース部分がほぼ完了。   
`exp_limit`の計算がなぜ、そうなるのか復習が必要。   

## 2025/11/19
`ft_atof/set_*`追加   

## 2025/11/20
`ft_atof/ft_strtod_str_to_mpn.c`の追加。`mpn->limbs`に加算を行う関数, 2^n(n > 0)する関数, 10倍する関数を追加。   
多倍長整数同士の掛け算、足し算をする関数の追加。   