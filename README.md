# NCファイルをマルチスレッドで読み込むライブラリ

NCデータのテキストファイルに記載された各行の座標を  
行頭のコマンドに従いリングバッファに読み込み  
アプリケーション側の要求に従い1行ずつデータを出力します。

## プロダクトコード

NCFileParser/NCFileLoader/

## GoogleTestによるユニットテストコード

NCFileParser/NCFileLoaderGoogleTest

## 本番データによる結合テストコード

NCFileParser/NCFileLoaderIFTest
