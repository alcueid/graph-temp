# savetempシェルスクリプトが出力したデータをグラフに出力するGNUPLOTスクリプト
# 画像への保存処理は別スクリプトが担当する

set xdata time                  # ソースのxは時刻と明示
set timefmt "%H:%M"             # ソースの時刻フォーマットを指定
set format x "%H:%M"            # x軸のラベルフォーマットを指定
set xtics rotate by -90         # x軸のラベルを-90度回転
plot src using 1:2 with lines  # 1,2列をソースに折れ線グラフに出力
pause -1


# エラー1
# plot "2018-02-05_temp.log" 
#                          ^
#"2018-02-05_script.plt", line 3: Need full using spec for x time data
# 時間情報をファイルから描画する場合にはusingオプションが必須
# http://takeno.iee.niit.ac.jp/~foo/gp-jman/data/20080929/gnuplot-ja-div/node76.html

# 横軸ラベルが重なるとき
# set xtics rotate by -90
# http://d.hatena.ne.jp/naga_sawa/20130109/1357717527

# Timefmt
# set timefmt "%H%M"
# http://takeno.iee.niit.ac.jp/~foo/gp-jman/data/gp372-jp-l2h/node218.html

# 時間の出力フォーマット
# 指定なしの場合%H:%M:%Sになる
# set format x "%H:%M"
# http://lowrank.net/gnuplot/datetime.html
