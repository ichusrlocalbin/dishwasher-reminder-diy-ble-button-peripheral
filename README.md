# ビーコン出力ボタン

## 作ろうとしたもの

* ボタンを押したら10秒程度ビーコンを出力する回路

## なぜ?

* [http://ichusrlocalbin.github.io/dishwasher-reminder](http://ichusrlocalbin.github.io/dishwasher-reminder) 参照

## そもそも

* 純粋な?自己保持回路（スイッチ入れたら数秒後に自動的に電源切る回路）は作るのがしんどそう。
* http://www.learningaboutelectronics.com/Articles/555-timer-delay-before-turn-off-circuit.php 使うだけで良さそう。LMC 555ってやつのデータシートを見ると、5V入力で0.1mAだから、220mAhのコイン電池使うと、2200時間=90日くらい持ちそう(待機電力だけだけど)。
* これにBLEのビーコンひたすら出力する回路をつなげば、スイッチ押した後10秒位BLE撒き散らして、自動的に回路断するものが作れそう。
* 単純に555の出力にBLE回路の電源につなげると2V程度に電圧降下してしまいビーコンが発生しなかった。そこで、オペアンプを使って比較回路の出力をBLEの回路の電源につなげた。
* 10秒程度の時間でC=10μF、R=1MΩ程度にしてボード上で確認したらうまく行ったが、なぜか、はんだ付けしたら?(電源をPCのUSBからコンセントからにしたから?)5秒程度に短くなったので(BLE nanoのビーコン発生を自作アプリで感知できなかった)ので、R=2.4MΩにした。

## 使ったチップ

* BLE-arudino: BLE Nano
* 555タイマー: TLC555SCP
* オペアンプ: TLV4112

## 回路図

![circuit image](https://ichusrlocalbin.github.io/images/posts/dishwasher-reminder/diy_beacon_button_circuit.jpg)

![button](https://ichusrlocalbin.github.io/images/posts/dishwasher-reminder/diy_beacon_button.jpg)

## 参考

### BLE Nano

#### http://homemadegarbage.0t0.jp/blenano-1

> 公式説明ではhttps://github.com/RedBearLab/nRF51822-Arduino/tree/S130/bootloaderのbootloader.hexをダウンロードし”MBED”ドライブにドラッグすれば良いとあるのですが、
> 全然正常に動作しません(基板の製造次期にもよるのか？)。。。。
> 以下、解決策です。
> * 上記でversion 1.0.5でインストールした”RedBearLab nRF51822 Boards”をversion 1.0.0でインストールし直します
> * C:\ユーザー\AppData\Local\Arduino15\packages\RedBearLab\hardware\nRF51822\1.0.0\bootloaders内にbootloader.hexが生成されてますので、これを”MBED”ドライブにドラッグするとBLE NanoのLEDが点滅しブートローダ状態になり正常に動作します。
> * このbootloader.hexはどこかに保存しといて”RedBearLab nRF51822 Boards”はversion 1.0.5で更新しなおします。
> * これでやっとArduinoで書き込めるようになりました♪
