# FTE09_chinchirorin
 FTE09ちんちろりんのメイン電装のソースコードです
 
 Aircraft_Aは上段電装
 
 Aircraft_Bは下段電装

# 開発環境
 IDE: Mbed Studio
 
 OS: Mbed OS 6.2.0

 Target: Mbed LPC1768
 
# 使用ライブラリ等
 [**IM920**](https://os.mbed.com/users/okini3939/code/IM920/), [**LPS331_I2C**](https://os.mbed.com/users/nyamfg/code/LPS331_I2C/), [**LSM9DS1**](https://os.mbed.com/users/zeutel/code/LSM9DS1/)
 
 ・各ライブラリを使いやすくするためにラップしたModuleWrapperを実装
 
 ・電装の実装をしやすくするためのAircraftBaseクラスを実装

 ・Mbed用にAircraftBaseクラスを継承したAircraftMbedBaseクラスを実装(使用モジュールLPS331AP, LSM9DS1, IM920の制限あり)
 
 ・分離条件や減速機構作動条件を個別にできるように、AircraftMbedBaseクラスを継承したAircraftクラスを実装

　上記のクラスは電装用フレームワークとして[**別リポジトリ**](https://github.com/FROM-THE-EARTH/Aircraft_Framework)で公開済み
 
# 注意書き
 Mbed OS 6になったことでいくつかのライブラリを書き換える必要があり、自力で書き換えているところがあります。
