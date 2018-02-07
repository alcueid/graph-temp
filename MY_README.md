# 修正したスクリプトやプログラムを旧バージョンより移行する際のメモ。
crondに毎分スクリプトを実行させるため、本ディレクトリのファイルを直接登録して実行させると編集中にスクリプトなどが正常に動かなくなる可能性がある。

# 手順
  1. master ブランチに切り替え
  2. Dropbox/software/in-use/graph-temp/date にコピー
  3. Dropbox/software/in-use/graph-temp/date を /opt/graph-temp/ にシンボリックリンクを貼る
