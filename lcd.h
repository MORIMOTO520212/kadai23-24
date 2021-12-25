/****************************************************************************************************/
/*		LCD表示ライブラリヘッダファイル	：	lcd.h													*/
/*																									*/
/*　本ヘッダファイルはOLED Display 0.96"ライブラリを使用するプログラムにてインクルードすること．			*/
/*　本ライブラリでは，twi.h及びtwi.cを利用しており，これらも同時にBuildする必要がある．					*/
/*　本I2C通信ライブラリは，OLED Display 0.96"がSDA及びSCL端子に接続され，LCDデバイスアドレスは0x78を		*/
/*　想定している．LCDデバイスアドレスを修正する場合は，LCD_ADRSのdefine値を修正すること					*/
/*																									*/
/*	変更履歴																							*/
/*　識別子	日付			氏名					変更内容													*/
/*　#000		2021.09.17	荒金 匡徳			初版リリース												*/
/****************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_
#include	"common.h"									/* 共通ヘッダファイル							*/
#include	"twi.h"										/* 基底クラス（twi）のヘッダファイル			*/
#include	<avr/pgmspace.h>							/* FONTをROM領域から読み出すためのヘッダ		*/

/* デバイスアドレス																					*/
#define LCD_ADRS	0x78								/* LCDデバイスのI2Cアドレス					*/

/* LCD Class 定義																					*/
class	LCD:public twi{
	/* font イメージバッファ（[4行][行上+行下][行当たり16文字][1文字当たり8Byte]	ビットマップデータ		*/
	char lcdImage[4][2][16][8];							/* OLED 表示イメージバッファ					*/
	/* キャラクタイメージバッファASCIIコード(0x20-0x7F）[4行][1行当たり16文字]ASCIIコードのデータ			*/
	char lcdChar[4][16];								/* OLED キャラクタバッファ					*/
  public:
	LCD( void);											/* コンストラクタ								*/
	void	lcdPrint( int x, int y, char *str);			/* LCDキャラクタバッファに文字を書き込む		*/
	void	lcdFlip();									/* LCDキャラクタバッファのイメージ展開表示		*/
	void	lcdClr(void);								/* LCDキャラクタ及びイメージバッファクリア		*/
	void	memFill( char *ptr, char data, int length);	/* メモリFillメソッド							*/
};

#endif /* LCD_H_ */