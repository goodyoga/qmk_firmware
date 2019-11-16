# The Reversed Helix Layout
## 配列

### Qwerty配列

```
        ,-----------------------------------------------------------------------------------.
        | ZKHK |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | ENT  |
 |------|------+------+------+------+------+------+------+------+------+------+------+-------------|
 |RAISE | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | SFT  |LOWER |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| CTL  | Alt  | GUI  |      |Lower |Space |Space |Raise | ALT  | GUI  | APP  | CTL  |Right |
 `-------------------------------------------------------------------------------------------------'
```

Helix キットの右と左を入れ替えて左右をくっつけてミニキーボードの用に使うコンフィグレーションです。

他レイヤーのキーマップについては reversed/keymap.c を参照してください。
RAISE で矢印＋Page系のキー、LOWER で記号系のキーというマップにしています。
また、ビルド・動作確認は Helix 5行版でのみ行っています。

## カスタマイズ
カスタマイズの方法は Helix default に準じます。
このコンフィグレーション用に追加したオプションのみ記載します。

### Slave 側で4行のロゴを使用する

Helix 標準では 3行×21文字でロゴを表示しますが、このオプションを有効にすると 4行×21文字でロゴを表示することができます。

4行のロゴを使用する場合は Slave用のフォントを helixfont_slave.h として用意する必要があります。
Slave 側の変数名は font_slave[] としてください。 ヘッダの二重インクルード防止の ifdef も FONT5X7_H の部分2箇所を FONT5X7_SLAVE_H に変更する必要があります。 
ロゴは ASCII コードの { 0x60-0x74, 0x80-0x94, 0xA0-0xB4, 0xC0-0xD4 } の領域に配置してください。 なお、slave 用に Master と同じデフォルトのフォントを使用すると、3行ロゴ下部に上下逆さまの小文字が表示されます。

現状は LOCAL_GLCDFONT 設定に依存していますので Master 側も helixfont.h を用意してください。
Master 側は helix/common/glcdfont.c の中身そのままコピペで大丈夫です。

rules.mk にて USE_SLAVE_FONT を yes に設定してください。


```
LOCAL_GLCDFONT    = yes     # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
USE_SLAVE_FONT    = yes     # use another font for slave.
```

また、この設定のために keymaps/ 以下のファイル以外に下記のファイルを変更していますので、必要に応じてこの fork から取得してください。
```
qmk_firmware/keyboards/helix/local_drivers/ssd1306.c
qmk_firmware/keyboards/helix/local_drivers/ssd1306.h
qmk_firmware/keyboards/helix/local_drivers/ssd1306.c
qmk_firmware/keyboards/helix/rev2/local_features.mk
```


keymap.c 側では
```
static void render_logo(struct CharacterMatrix *matrix) {
  static char logo[]={
#if defined(USE_SLAVE_FONT)
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,
#endif
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}
```

にするのと

```
void iota_gfx_task_user(void) {
  struct CharacterMatrix *p_matrix = matrix_getInstance();

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

#if defined(USE_SLAVE_FONT)
  matrix_set_page_mode(!is_master);
  matrix_set_font_no(is_master ? 0 : 1);
#endif
  matrix_clear(p_matrix);
  if(is_master){
    render_status(p_matrix);
  }else{
    render_logo(p_matrix);
  }
}
```

の変更で Slave 用フォントが使用され、4行のロゴが表示できます。

master_set_page_mode() で page_mode を true にを設定しないと、ssd1306 ドライバのデフォルト動作として画面いっぱいに4行ロゴの描画が終わった時点で1行スクロールされます。 また、qmk/qmk_firmware オリジナルのコードではローカル変数の struct CharacterMatrix matrix に設定した内容を ssd1306.c::display にコピーするようになっていましたが、 page_mode の設定がうまく伝わらないタイミングがあるのかロゴがちらつきましたので、直接 matrix_getInstance() で ssd1306.c のインスタンスを取得し Update するように変更しました。

build
```
$ make helix:reversed
```

flash to keyboard
```
$ make helix:reversed:flash

```

## リンク

* さらに詳細は、[こちら helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)をご覧ください。
* [Helix top](https://github.com/MakotoKurauchi/helix)
