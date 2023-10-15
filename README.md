# AviUtl_FSR1_filter_plugin

[AviUtl](http://spring-fragrance.mints.ne.jp/aviutl/)向けの、[FidelityFX Super Resolution 1.0 (FSR)](https://github.com/GPUOpen-Effects/FidelityFX-FSR)を用いた画像拡大を行うプラグイン。  

## 動作確認環境  
AviUtl version 1.10  
Microsoft Windows [Version 10.0.22621.2428]  

## ビルド環境  
Visual Studio Community (64 ビット) Version 17.7.5  
AviUtl Plugin SDK for ver0.99m以降  
Windows Implementation Libraries (WIL) v1.0.230824.2  

## 使用方法  
fsr1.auf を 『aviutl.exe と同じディレクトリ』或いは『aviutl.exe があるディレクトリの Plugins ディレクトリ』にコピーし、aviutl.exe を起動する。  

## プラグインの設定項目  
- W:  
出力画像の幅  

- H:  
出力画像の高さ  

- #:  
出力画像の鋭さ(推奨値は80)  

- Compatible Convert:  
フォーマット変換の方法と保持データの精度を決定する。チェック時、AviUtl と互換性が高い変換を行うが精度は低い。非チェック時、互換性が低い変換を行うが精度は高い。  
