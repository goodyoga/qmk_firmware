# The Reversed Helix Layout
## 配列

### Qwerty配列

```
        ,-----------------------------------------------------------------------------------.
        |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  | BS   |
        |------+------+------+------+------+------+------+------+------+------+------+------|
        | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | [    |
        |------+------+------+------+------+------+------+------+------+------+------+------|
        | CTL  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | ENT  |
 |------|------+------+------+------+------+------+------+------+------+------+------+------+------|
 | RAISE| SH   |   /  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | SH   | LOWER|
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 | ADJ  | CTL  | LGUI | Alt  |   _  |LOWER |Space |Space |RAISE | ALT  | RGUI | APP  | CTL  | ADJ  |
 `-------------------------------------------------------------------------------------------------'
```

Helix キットの右と左を入れ替えて左右をくっつけて 60% キーボードの様に使うコンフィグレーションです。

他レイヤーのキーマップについては reversed/keymap.c を参照してください。
RAISE で矢印＋Page系のキー、LOWER で記号系のキーというマップにしています。
また、ビルド・動作確認は Helix 5行版でのみ行っています。

## カスタマイズ
カスタマイズの方法は Helix default に準じます。
このコンフィグレーション用に追加したオプションのみ記載します。


### Slave 側で4行のロゴを使用する

Helix 標準では 21文字×3行でロゴを表示しますが、このオプションを有効にすると 21文字×4行でロゴを表示することができます。

#### フォントファイルの準備

4行のロゴを使用する場合は Slave専用のフォントを helixfont_slave.h として用意する必要があります。

Slave 側の変数名は font_slave[] としてください。

ヘッダの二重インクルード防止の ifdef も FONT5X7_H の部分2箇所を FONT5X7_SLAVE_H に変更する必要があります。

巷の Web サービスでフォントファイルを編集している場合には、_slave, _SLAVE の部分を一旦もとに戻す必要があると思いますのでご注意ください。


ロゴは ASCII コードの { 0x60-0x74, 0x80-0x94, 0xA0-0xB4, 0xC0-0xD4 } の領域に配置してください。 
なお、RAM/Flash 節約のため、 Slave側フォントの文字コードは { 0x01-0x15, ... } に移動し、コード 0x80 以降のフォントを削除可能にする予定です。


#### Master 側フォントとの棲み分け
蛇足ですが、このオプションを有効にした状態で slave 用に Master と同じデフォルトのフォントを使用しても、3行ロゴ下部に上下逆さまの小文字が表示されるだけでキーボードとしては動作します。 render_logo() 内の static char logo[] で表示する領域を変更すれば表示可能文字のフォントの実際のディスプレイでの見栄え確認にも使えると思いますので、そういった使い方も良いかと思います。

Master 側のコード 0x80 以降のフォント領域は完全に Master 専用のフリー領域となりますので、カスタムキーの表示用アイコン(Helix 標準ではリンゴ、Win、Tux が 0x95 近辺に入っているだけ)などに活用できます。 Master 側のフォントを変更する場合は、標準オプションの LOCAL_GLCDFONT = yes と helixfont.h を使用してください。



#### 設定
rules.mk にて USE_SLAVE_FONT を yes に設定してください。


```
USE_SLAVE_FONT    = yes     # use another font for slave.
```

#### コードの変更

この設定のために keymaps/ 以下のファイル以外に下記のファイルを変更していますので、必要に応じてこの fork から取得してください。

```
qmk_firmware/keyboards/helix/local_drivers/ssd1306.c
qmk_firmware/keyboards/helix/local_drivers/ssd1306.h
qmk_firmware/keyboards/helix/local_drivers/ssd1306.c
qmk_firmware/keyboards/helix/rev2/local_features.mk
```


keymap.c 側では
```
static  long unsigned int  logo_state = 0;
#define  LOGO_STATE_TMO   10000

static void render_logo(struct CharacterMatrix *matrix)
 {
    static char logo[]={
#if defined(USE_SLAVE_FONT)
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,
#endif
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};

    if (  0 == (logo_state % LOGO_STATE_TMO ) )
    {
        matrix_clear(matrix);
        matrix_write(matrix, logo);
        logo_state++;
    }
}
```

にするのと

```
#define L_UNDEF  (-1)


static layer_state_t  old_layer_state = L_UNDEF;

void render_status(struct CharacterMatrix *matrix)
{
    char buf[40];

    if (old_layer_state == layer_state)
        return;

    matrix_clear(matrix);
    snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);

    switch (layer_state) {
    case L_BASE:
        matrix_write_P(matrix, PSTR(" Q W E R T Y "));
        break;
    case L_RAISE:
        matrix_write_P(matrix, PSTR("  R A I S E  "));
        break;
    case L_LOWER:
        matrix_write_P(matrix, PSTR("      ' / * @ - = \\\n"));
        matrix_write_P(matrix, PSTR("! \" # $ % & { } [ ]\n"));
        matrix_write_P(matrix, PSTR("@ ` * \\ | ; : \" ( )\n"));
        matrix_write_P(matrix, PSTR("^ ~ _ - + _ , . /"));
        break;
    case L_ADJUST:
    case L_ADJUST_TRI:
    {
        char l2[] = { 0x20,0x20, 0x80,0x20, 0x81,0x20, '\n', 0x00 };
        char l3[] = { 0x20,0x20, 0x83,0x20, 0x84,0x20, 0x85,0x86, 0x20,0x20, 0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,'\n', 0x00 };
        char l4[] = { 0x20,0x20, 0x20,0x20, 0x20,0x20, 0x20,0x20, 0x20,0x20, 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7, 0x00 };
 
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write(matrix, l2);
        matrix_write(matrix, l3);
        matrix_write(matrix, l4);
        break;
    }
    default:
        matrix_write(matrix, buf);
    }
    old_layer_state = layer_state;
}


void iota_gfx_task_user(void)
{
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
    if (is_master) {  render_status(p_matrix);  }
    else           {  render_logo(p_matrix);    }
}

```

の変更で Slave 用フォントが使用され、4行のロゴが表示できます。 上記のコードには4行ロゴ以外の変更も含まれていますがご了承ください。

#### その他
##### master_set_page_mode()
ssd1306 ドライバのデフォルト動作として画面いっぱいに4行ロゴの描画が終わった時点で1行スクロールされます。 master_set_page_mode() で page_mode を true に設定することで、描画済みのものをスクロールせずに画面先頭にカーソルだけ移動するようなります。

##### master_set_font_no()
master_set_font_no() に 1 を入れることで Slave フォントを使用します。 0 だと Master フォントを使用します。

また、qmk/qmk_firmware オリジナルのコードではローカル変数の struct CharacterMatrix matrix に仮設定した内容とオリジナルを比較して ssd1306.c::display にコピーするようになっていましたが、 page_mode の設定がうまく伝わらなくてロゴがちらつきますので、直接 matrix_getInstance() で ssd1306.c のインスタンスを取得し Update するように変更しました。

インスタンスの直接編集の弊害で起こるタイムアウトで描画を消す対応と毎回描画するとキーを取りこぼす頻度が高い対策は別途入れてあります。 matrix_clear(); を render_status() と render_logo() に移動し、render_*() での描画は変更があったときのみになるように state 変数を導入しています。

将来的には ssd1306.c 側をダブルバッファにして(ssd1306側で比較することで)、keymap.c 側では更新の有無を意識しなくて済む構成にしたいです。




### 左のHelix と 右Helix の入れ替え
Helix 標準では 中央に OLED Display が来るように左右を配置しますが、両端に OLED Display が来るように配置できるようになります。

#### 設定
rules.mk にて REVERSED_COL_PINS_KEYMAP を yes に設定してください。


```
REVERSED_COL_PINS_KEYMAP = yes   # Left is right side, Right is left side
```

config の名前がイマイチなので変更する予定です。


#### コードの変更

この設定のために keymaps/ 以下のファイル以外に下記のファイルを変更していますので、必要に応じてこの fork から取得してください。

```
qmk_firmware/keyboards/helix/rev2/local_features.mk
qmk_firmware/keyboards/helix/rev2/rev2.h
```

keymap.c には通常と同様に見た目と同じ順序で記述可能です。




### RGBTEST

本家 QMK の RGBTEST(helix/rev2/keymap/led_test でも使用) は本当に R,G,B の3色しか表示しません。
(R,G,B)=(1,0,0),(0,1,0),(0,0,1) の3パターンだけだとLED のハンダ不良が見分けにくいので、(R,G,B)=(0,0,0),(0,0,1),(0,1,0),(0,1,1),...(1,1,1)  の様に各色 ON と OFF の全ての組み合わせを点灯させるように変更しています。

#### 設定
本家のコードを直接変更していますので、rurles.mk で設定可能なコンフィグはありません。

#### コードの変更

この設定のために keymaps/ 以下のファイル以外に下記のファイルを変更していますので、必要に応じてこの fork から取得してください。

```
qmk_firmware/quantum/rgblight.c
```

なお、変更したのは rgblight_effect_rgbtest() です。

#### その他
変更した RGBTEST は make  helix:led_test でビルドすると使えます。





### build
```
$ make helix:reversed
```

flash to keyboard
```
$ make helix:reversed:avrdude

```

## リンク

* さらに詳細は、[こちら helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)をご覧ください。
* [Helix top](https://github.com/MakotoKurauchi/helix)
