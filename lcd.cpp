/****************************************************************************************************/
/*　LCD class																						*/
/*																									*/
/*　本ファイルはOLED Displayに文字を表示するクラスのメソッドを定義したものである．							*/
/*　本クラスはtwiクラスを継承しており，これらも同時にBuildする必要がある．								*/
/*　基本FONTデータも本ファイルにて定義している．														*/
/*　想定している．LCDデバイスアドレスを修正する場合は，LCD_ADRSのdefine値を修正すること．					*/
/*																									*/
/*	■メソッド一覧																						*/
/*			LCDクリア		：void	lcdClr(void)													*/
/*			LCD表示			：void	lcdPrint( int x, int y, char *str)								*/
/*			LCDフリップ		：void	lcdFlip(void)													*/
/*			メモリFill		：void	memfill( char *ptr, char data, int length)						*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/****************************************************************************************************/
/*	変更履歴																							*/
/*　識別子	日付			氏名					変更内容													*/
/*　#000		2021.07.26	荒金 匡徳			初版リリース												*/
/****************************************************************************************************/
#include	"twi.h"										/* I2Cドライバ用ヘッダファイル				*/
#include	"lcd.h"										/* LCD クラス定義ファイル						*/

/* FONTデータはメモリのdata領域に配置すると変数が殆ど作れなくなってしまうため，PROGMEM領域に配置			*/
const char	fnt[1536] PROGMEM = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x20 ' '	*/
	0x00,0x00,0x3c,0xfe,0xfe,0x3c,0x00,0x00, 0x00,0x00,0x00,0x0d,0x0d,0x00,0x00,0x00,	/* 0x21 '!'	*/
	0x00,0x0e,0x1e,0x00,0x00,0x1e,0x0e,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x22 '"'	*/
	0x30,0xfe,0xfe,0x30,0xfe,0xfe,0x30,0x00, 0x03,0x1f,0x1f,0x03,0x1f,0x1f,0x03,0x00,	/* 0x23 '#'	*/
	0x38,0x7c,0x44,0xff,0xff,0x44,0xcc,0x88, 0x06,0x0e,0x08,0x3f,0x3f,0x08,0x0f,0x07,	/* 0x24 '$'	*/
	0x1c,0x14,0x9c,0xe0,0x78,0x1c,0x04,0x00, 0x08,0x0e,0x07,0x01,0x0e,0x0a,0x0e,0x00,	/* 0x25 '%'	*/
	0x80,0xdc,0x7e,0xe2,0xbe,0xdc,0x40,0x00, 0x07,0x0f,0x08,0x09,0x07,0x0f,0x08,0x00,	/* 0x26 '&'	*/
	0x00,0x00,0x10,0x1e,0x0e,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x27 '''	*/
	0x00,0x00,0xf8,0xfe,0x07,0x01,0x00,0x00, 0x00,0x00,0x03,0x0f,0x1c,0x10,0x00,0x00,	/* 0x28 '('	*/
	0x00,0x00,0x01,0x07,0xfe,0xf8,0x00,0x00, 0x00,0x00,0x10,0x1c,0x0f,0x03,0x00,0x00,	/* 0x29 ')'	*/
	0x80,0xa0,0xe0,0xc0,0xc0,0xe0,0xa0,0x80, 0x00,0x02,0x03,0x01,0x01,0x03,0x02,0x00,	/* 0x2a '*'	*/
	0x00,0x80,0x80,0xe0,0xe0,0x80,0x80,0x00, 0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,	/* 0x2b '+'	*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x20,0x3c,0x1c,0x00,0x00,0x00,	/* 0x2c ','	*/
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x2d '-'	*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x0c,0x0c,0x00,0x00,0x00,0x00,	/* 0x2e '.'	*/
	0x00,0x00,0xc0,0xf0,0x3c,0x0e,0x02,0x00, 0x0c,0x0f,0x03,0x00,0x00,0x00,0x00,0x00,	/* 0x2f '/'	*/

	0xf8,0xfc,0x86,0xf2,0x3e,0xfc,0xf8,0x00, 0x03,0x07,0x0f,0x09,0x0c,0x07,0x03,0x00,	/* 0x30 '0'	*/
	0x00,0x08,0x0c,0xfe,0xfe,0x00,0x00,0x00, 0x00,0x08,0x08,0x0f,0x0f,0x08,0x08,0x00,	/* 0x31 '1'	*/
	0x18,0x1c,0x06,0x82,0xc6,0x7c,0x38,0x00, 0x0c,0x0e,0x0b,0x09,0x08,0x0c,0x0c,0x00,	/* 0x32 '2'	*/
	0x06,0x02,0x32,0x3a,0x6e,0xc6,0x80,0x00, 0x02,0x06,0x0c,0x08,0x0c,0x07,0x03,0x00,	/* 0x33 '3'	*/
	0x80,0xe0,0x78,0x1e,0xfe,0xfe,0x00,0x00, 0x01,0x01,0x01,0x09,0x0f,0x0f,0x09,0x00,	/* 0x34 '4'	*/
	0x3e,0x3e,0x12,0x12,0x32,0xe2,0xc2,0x00, 0x02,0x06,0x0c,0x08,0x0c,0x07,0x03,0x00,	/* 0x35 '5'	*/
	0xf8,0xfc,0x66,0x22,0x66,0xc4,0x80,0x00, 0x03,0x07,0x0c,0x08,0x0c,0x07,0x03,0x00,	/* 0x36 '6'	*/
	0x06,0x06,0x02,0xc2,0xf2,0x3e,0x0e,0x00, 0x00,0x00,0x0f,0x0f,0x00,0x00,0x00,0x00,	/* 0x37 '7'	*/
	0x18,0xbc,0xe6,0x42,0xe6,0xbc,0x18,0x00, 0x03,0x07,0x0c,0x08,0x0c,0x07,0x03,0x00,	/* 0x38 '8'	*/
	0x38,0x7c,0xc6,0x82,0xc6,0xfc,0xf8,0x00, 0x00,0x04,0x0c,0x08,0x0c,0x07,0x03,0x00,	/* 0x39 '9'	*/
	0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00, 0x00,0x00,0x00,0x0c,0x0c,0x00,0x00,0x00,	/* 0x3a ':'	*/
	0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00, 0x00,0x20,0x30,0x1c,0x0c,0x00,0x00,0x00,	/* 0x3b ';'	*/
	0x00,0x80,0xc0,0x60,0x30,0x18,0x08,0x00, 0x00,0x00,0x01,0x03,0x06,0x0c,0x08,0x00,	/* 0x3c '<'	*/
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00, 0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,	/* 0x3d '='	*/
	0x00,0x08,0x18,0x30,0x60,0xc0,0x80,0x00, 0x00,0x08,0x0c,0x06,0x03,0x01,0x00,0x00,	/* 0x3e '>'	*/
	0x08,0x0c,0x06,0x82,0xc2,0x66,0x3c,0x18, 0x00,0x00,0x00,0x0d,0x0d,0x00,0x00,0x00,	/* 0x3f '?'	*/

	0xf0,0xf8,0x08,0xc8,0xc8,0xf8,0xf0,0x00, 0x07,0x0f,0x08,0x0b,0x0b,0x0b,0x01,0x00,	/* 0x40 '@'	*/
	0xf0,0xf8,0x1c,0x0e,0x1c,0xf8,0xf0,0x00, 0x0f,0x0f,0x01,0x01,0x01,0x0f,0x0f,0x00,	/* 0x41 'A'	*/
	0x02,0xfe,0xfe,0x22,0x22,0xfe,0xdc,0x00, 0x08,0x0f,0x0f,0x08,0x08,0x0f,0x07,0x00,	/* 0x42 'B'	*/
	0xfc,0xfe,0x02,0x02,0x02,0x0e,0x0c,0x00, 0x07,0x0f,0x08,0x08,0x08,0x0e,0x06,0x00,	/* 0x43 'C'	*/
	0x02,0xfe,0xfe,0x02,0x06,0xfc,0xf8,0x00, 0x08,0x0f,0x0f,0x08,0x0c,0x07,0x03,0x00,	/* 0x44 'D'	*/
	0x02,0xfe,0xfe,0x42,0xe2,0x06,0x0e,0x00, 0x08,0x0f,0x0f,0x08,0x08,0x0c,0x0e,0x00,	/* 0x45 'E'	*/
	0x02,0xfe,0xfe,0x42,0xe2,0x06,0x0e,0x00, 0x08,0x0f,0x0f,0x08,0x00,0x00,0x00,0x00,	/* 0x46 'F'	*/
	0xfc,0xfe,0x02,0x02,0x82,0x9e,0x9c,0x00, 0x07,0x0f,0x08,0x08,0x0c,0x07,0x0f,0x00,	/* 0x47 'G'	*/
	0xfe,0xfe,0x40,0x40,0x40,0xfe,0xfe,0x00, 0x0f,0x0f,0x00,0x00,0x00,0x0f,0x0f,0x00,	/* 0x48 'H'	*/
	0x00,0x00,0x02,0xfe,0xfe,0x02,0x00,0x00, 0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00,	/* 0x49 'I'	*/
	0x00,0x00,0x00,0x02,0xfe,0xfe,0x02,0x00, 0x06,0x0e,0x08,0x08,0x0f,0x07,0x00,0x00,	/* 0x4a 'J'	*/
	0x02,0xfe,0xfe,0xe0,0xf8,0x1e,0x06,0x00, 0x08,0x0f,0x0f,0x00,0x03,0x0f,0x0c,0x00,	/* 0x4b 'K'	*/
	0x02,0xfe,0xfe,0x02,0x00,0x00,0x00,0x00, 0x08,0x0f,0x0f,0x08,0x08,0x0c,0x0e,0x00,	/* 0x4c 'L'	*/
	0xfe,0xfc,0x38,0xf0,0x38,0xfc,0xfe,0x00, 0x0f,0x0f,0x00,0x00,0x00,0x0f,0x0f,0x00,	/* 0x4d 'M'	*/
	0xfe,0xfe,0x78,0xe0,0x80,0xfe,0xfe,0x00, 0x0f,0x0f,0x00,0x00,0x03,0x0f,0x0f,0x00,	/* 0x4e 'N'	*/
	0xfc,0xfe,0x02,0x02,0x02,0xfe,0xfc,0x00, 0x07,0x0f,0x08,0x08,0x08,0x0f,0x07,0x00,	/* 0x4f 'O'	*/

	0x02,0xfe,0xfe,0x82,0x82,0xfe,0x7c,0x00, 0x08,0x0f,0x0f,0x08,0x00,0x00,0x00,0x00,	/* 0x50 'P'	*/
	0xfc,0xfe,0x02,0x02,0x02,0xfe,0xfc,0x00, 0x07,0x0f,0x0c,0x0e,0x1e,0x3f,0x37,0x00,	/* 0x51 'Q'	*/
	0x02,0xfe,0xfe,0x82,0xc2,0x7e,0x3c,0x00, 0x08,0x0f,0x0f,0x00,0x01,0x0f,0x0e,0x00,	/* 0x52 'R'	*/
	0x1c,0x3e,0x62,0x42,0xc2,0x8e,0x0c,0x00, 0x06,0x0e,0x08,0x08,0x08,0x0f,0x07,0x00,	/* 0x53 'S'	*/
	0x00,0x06,0x02,0xfe,0xfe,0x02,0x06,0x00, 0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00,	/* 0x54 'T'	*/
	0xfe,0xfe,0x00,0x00,0x00,0xfe,0xfe,0x00, 0x07,0x0f,0x08,0x08,0x08,0x0f,0x07,0x00,	/* 0x55 'U'	*/
	0xfe,0xfe,0x00,0x00,0x00,0xfe,0xfe,0x00, 0x01,0x03,0x06,0x0e,0x06,0x03,0x01,0x00,	/* 0x56 'V'	*/
	0xfe,0xfe,0x00,0xe0,0xe0,0x00,0xfe,0xfe, 0x03,0x0f,0x0e,0x03,0x03,0x0e,0x0f,0x03,	/* 0x57 'W'	*/
	0x06,0x1e,0xf8,0xe0,0xf8,0x1e,0x06,0x00, 0x0c,0x0f,0x03,0x00,0x03,0x0f,0x0c,0x00,	/* 0x58 'X'	*/
	0x00,0x3e,0x7e,0xc0,0xc0,0x7e,0x3e,0x00, 0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00,	/* 0x59 'Y'	*/
	0x0e,0x06,0x82,0xe2,0x3a,0x1e,0x06,0x00, 0x0c,0x0f,0x0b,0x08,0x08,0x0c,0x0e,0x00,	/* 0x5a 'Z'	*/
	0x00,0x00,0xfe,0xfe,0x02,0x02,0x00,0x00, 0x00,0x00,0x0f,0x0f,0x08,0x08,0x00,0x00,	/* 0x5b '['	*/
	0x06,0x1e,0x78,0xe0,0x80,0x00,0x00,0x00, 0x00,0x00,0x00,0x01,0x07,0x0e,0x08,0x00,	/* 0x5c '\'	*/
	0x00,0x00,0x02,0x02,0xfe,0xfe,0x00,0x00, 0x00,0x00,0x08,0x08,0x0f,0x0f,0x00,0x00,	/* 0x5d ']'	*/
	0x10,0x18,0x0c,0x06,0x0c,0x18,0x10,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x5e '^'	*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	/* 0x5f '_'	*/

	0x00,0x00,0x0e,0x1e,0x10,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* 0x60 '`'	*/
	0x00,0xa0,0xa0,0xa0,0xe0,0xc0,0x00,0x00, 0x07,0x0f,0x08,0x08,0x07,0x0f,0x08,0x00,	/* 0x61 'a'	*/
	0x02,0xfe,0xfe,0x20,0x20,0xe0,0xc0,0x00, 0x08,0x0f,0x07,0x08,0x08,0x0f,0x07,0x00,	/* 0x62 'b'	*/
	0xc0,0xe0,0x20,0x20,0x20,0x60,0x40,0x00, 0x07,0x0f,0x08,0x08,0x08,0x0c,0x04,0x00,	/* 0x63 'c'	*/
	0xc0,0xe0,0x20,0x22,0xfe,0xfe,0x00,0x00, 0x07,0x0f,0x08,0x08,0x07,0x0f,0x08,0x00,	/* 0x64 'd'	*/
	0xc0,0xe0,0x20,0x20,0x20,0xe0,0xc0,0x00, 0x07,0x0f,0x09,0x09,0x09,0x0d,0x04,0x00,	/* 0x65 'e'	*/
	0x20,0xfc,0xfe,0x22,0x02,0x0e,0x0c,0x00, 0x08,0x0f,0x0f,0x08,0x00,0x00,0x00,0x00,	/* 0x66 'f'	*/
	0xc0,0xe0,0x20,0x20,0xc0,0xe0,0x20,0x00, 0x47,0xcf,0x88,0x88,0xff,0x7f,0x00,0x00,	/* 0x67 'g'	*/
	0x02,0xfe,0xfe,0x20,0x20,0xe0,0xc0,0x00, 0x08,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00,	/* 0x68 'h'	*/
	0x00,0x00,0x20,0xec,0xec,0x00,0x00,0x00, 0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00,	/* 0x69 'i'	*/
	0x00,0x00,0x00,0x20,0xec,0xec,0x00,0x00, 0x60,0xe0,0x80,0x80,0xff,0x7f,0x00,0x00,	/* 0x6a 'j'	*/
	0x02,0xfe,0xfe,0x00,0x80,0xe0,0x60,0x00, 0x08,0x0f,0x0f,0x01,0x03,0x0e,0x0c,0x00,	/* 0x6b 'k'	*/
	0x00,0x00,0x02,0xfe,0xfe,0x00,0x00,0x00, 0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00,	/* 0x6c 'l'	*/
	0xe0,0xe0,0x60,0xc0,0x60,0xe0,0xc0,0x00, 0x0f,0x0f,0x00,0x03,0x00,0x0f,0x0f,0x00,	/* 0x6d 'm'	*/
	0x20,0xe0,0xc0,0x20,0x20,0xe0,0xc0,0x00, 0x00,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00,	/* 0x6e 'n'	*/
	0xc0,0xe0,0x20,0x20,0x20,0xe0,0xc0,0x00, 0x07,0x0f,0x08,0x08,0x08,0x0f,0x07,0x00,	/* 0x6f 'o'	*/

	0x20,0xe0,0xc0,0x20,0x20,0xe0,0xc0,0x00, 0x80,0xff,0xff,0x88,0x08,0x0f,0x07,0x00,	/* 0x70 'p'	*/
	0xc0,0xe0,0x20,0x20,0xc0,0xe0,0x20,0x00, 0x07,0x0f,0x08,0x88,0xff,0xff,0x80,0x00,	/* 0x71 'q'	*/
	0x20,0xe0,0xc0,0x60,0x20,0xe0,0xc0,0x00, 0x08,0x0f,0x0f,0x08,0x00,0x00,0x00,0x00,	/* 0x72 'r'	*/
	0xc0,0xe0,0x20,0x20,0x20,0x60,0x40,0x00, 0x04,0x0d,0x09,0x09,0x09,0x0f,0x06,0x00,	/* 0x73 's'	*/
	0x20,0x20,0xfc,0xfe,0x20,0x20,0x00,0x00, 0x00,0x00,0x07,0x0f,0x08,0x0c,0x04,0x00,	/* 0x74 't'	*/
	0xe0,0xe0,0x00,0x00,0x00,0xe0,0xe0,0x00, 0x07,0x0f,0x08,0x08,0x08,0x07,0x0f,0x08,	/* 0x75 'u'	*/
	0xe0,0xe0,0x00,0x00,0x00,0xe0,0xe0,0x00, 0x01,0x03,0x07,0x0e,0x07,0x03,0x01,0x00,	/* 0x76 'v'	*/
	0xe0,0xe0,0x00,0x80,0x00,0xe0,0xe0,0x00, 0x07,0x0f,0x0c,0x07,0x0c,0x0f,0x07,0x00,	/* 0x77 'w'	*/
	0x60,0xe0,0xc0,0x80,0xc0,0xe0,0x60,0x00, 0x0c,0x0e,0x07,0x03,0x07,0x0e,0x0c,0x00,	/* 0x78 'x'	*/
	0xe0,0xe0,0x00,0x00,0x00,0xe0,0xe0,0x00, 0x07,0x4f,0x48,0x48,0x48,0x7f,0x3f,0x00,	/* 0x79 'y'	*/
	0x60,0x60,0x20,0x20,0xa0,0xe0,0x60,0x00, 0x0c,0x0e,0x0b,0x09,0x09,0x0c,0x0c,0x00,	/* 0x7a 'z'	*/
	0x40,0x40,0xe0,0xbe,0x1f,0x01,0x01,0x00, 0x00,0x00,0x00,0x0f,0x1f,0x10,0x10,0x00,	/* 0x7b '{'	*/
	0x00,0x00,0x00,0x3e,0x3e,0x00,0x00,0x00, 0x00,0x00,0x00,0x1f,0x1f,0x00,0x00,0x00,	/* 0x7c '|'	*/
	0x00,0x01,0x01,0x1f,0xbe,0xe0,0x40,0x40, 0x00,0x10,0x10,0x1f,0x0f,0x00,0x00,0x00,	/* 0x7d '}'	*/
	0x40,0xe0,0x50,0x48,0x40,0x40,0x40,0x00, 0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,	/* 0x7e '<-'*/
	0x00,0x00,0x0c,0x12,0x12,0x0c,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	/* 0x7F 'o'度*/
};


/****************************************************************************************************/
/* コンストラクタ		：LCD( void)																		*/
/*																									*/
/* 機能　：基底クラスのコンストラクタ(twi)にOLED Displayデバイスのアドレスを渡し，twi通信の初期化を行う．	*/
/*		  OLED Display の初期化を行う．																*/
/*																									*/
/* 引数　：なし																						*/
/*																									*/
/* 戻り値：なし																						*/
/****************************************************************************************************/
LCD::LCD( void):twi( LCD_ADRS){							/* OLED Display 初期化						*/
	twiStart();											/* デバイスアドレスを指定して送信開始			*/
	twiSend(0b00000000);								/* 制御byte Co = 0 (継続) D/C# = 0 (コマンド)	*/
	twiSend(0xAE);										/* 表示 off									*/
	twiSend(0xA8);										/* Multiplex Ratio を64に設定				*/
	twiSend(0b00111111);
	twiSend(0xD3);										/* 表示オフセット：原点のまま					*/
	twiSend(0x00);
	twiSend(0x40);										/* 表示開始行を先頭にセット					*/
	twiSend(0xA0);										/* 表示データ-セグメントデータ間オフセット初期化*/
	twiSend(0xC0);										/* COM 出力スキャン方向設定：順方向			*/
	twiSend(0xDA);										/* COM ピンハードウェア設定					*/
	twiSend(0b00010010);
	twiSend(0x81);										/* コントラスト(明るさ)設定					*/
	twiSend(255);										/* 最大輝度									*/
	twiSend(0xA4);										/* メモリ内のコンテンツ表示ON					*/
	twiSend(0xA6);										/* メモリ内通常表示(1：白/0：黒）				*/
	twiSend(0xD5);										/* 表示クロック設定							*/
	twiSend(0b10000000);
	twiSend(0x2E);										/* スクロール表示無効設定						*/
	twiSend(0x21);										/* メモリのスタートカラムと終了カラムの設定		*/
	twiSend(0);											/* 水平開始位置								*/
	twiSend(127);										/* 水平位置終了位置							*/
	twiSend(0x22);										/* メモリのページアドレス設定					*/
	twiSend(0);											/* 垂直開始位置（0ページ）					*/
	twiSend(7);											/* 垂直終了位置（7ページ）					*/
	twiSend(0x8D);										/* チャージポンプ設定（7.5V)					*/
	twiSend(0x14);
	twiSend(0xAF);										/* 標準モードで Display On					*/
	twiStop();
	/* 表示メモリクリア																				*/
	memFill(&lcdChar[0][0],0x20,4*16);					/* キャラクタバッファクリア					*/
	lcdFlip();											/* LCDに空白を出力							*/
}

/****************************************************************************************************/
/* LCDクリア			：void	lcdClr(void)															*/
/*																									*/
/* 機能　：LCDキャラクタバッファ（lcd_chr[4][16]）及び表示イメージバッファ(lcd_img[4][2][16][8]）			*/
/*		　をクリアする																				*/
/* 引数　：なし																						*/
/*																									*/
/* 戻り値：なし																						*/
/*																									*/
/* 備考　：LCDキャラクタバッファは空白で，表示イメージバッファは0x00で埋める．								*/
/****************************************************************************************************/
void	LCD::lcdClr(void){
	memFill(&lcdImage[0][0][0][0],0x00,2*4*16*8);		/* 表示イメージバッファクリア					*/
	memFill(&lcdChar[0][0],0x20,4*16);					/* キャラクタバッファクリア					*/
}

/****************************************************************************************************/
/* LCD表示			：void	lcdPrint( int x, int y, char *str)										*/
/*																									*/
/* 機能　：LCDのキャラクタバッファにデータを書き込む．（LCDへの表示はlcd_flipメソッド実行時に行われる）		*/
/*																									*/
/* 引数　：int	x				：　書き込むカラム番号（左から何文字目か）								*/
/*		  int	y				：　書き込む行番号（上から何行目か）									*/
/*		  char	*str			：　書き込むデータの先頭アドレス										*/
/*																									*/
/* 戻り値：なし																						*/
/*																									*/
/* 備考　：指定する行番号及びカラム番号は，もともと4行（0〜3）16文字（0〜15）を想定しているが，自動改行を	*/
/*		  想定し，例えば(x,y)を(16,0)と指定しても(0,1)と指定したのと同じ結果が得られる．					*/
/*		  また，3行目を超えた場合は0行目に折り返す．よって，(x,y)を（16,3）と指定しても(0,0)と指定したのと	*/
/*		  同じ結果が得られる．																		*/
/*		  書き込むデータはASCIIコードで0x20〜0x7Fの範囲を有効とし，これ以外のコードが出てきた段階で		*/
/*		  キャラクタバッファへの転送を終了する．（NULL終端推奨）											*/
/****************************************************************************************************/
void	LCD::lcdPrint( int x, int y, char *str){
	y = y + x/16;										/* xが1行の文字数を超えていた場合,改行処理を行う*/
	x %= 16;
	y %= 4;												/* yが3行目を超えた場合は0行目に戻る			*/
	while((*str >= 0x20)&&(*str <= 0x7f)){				/* 次に書き込むデータが範囲内の間処理を行う		*/
		lcdChar[y][x] = *str;							/* キャラクタバッファに1Byteデータを書き込む	*/
		str++;											/* 元データのポインタを進める					*/
		x++;											/* LCDキャラクタバッファのカラムを進める		*/
		if( x > 15){									/* 1行の文字数をオーバーしたとき				*/
			x = 0;										/* 行の先頭に戻る							*/
			y++;										/* 行を1行下げる								*/
			if(y > 3){									/* 最下行を超えたとき							*/
				y = 0;									/* 先頭行を指定する							*/
			}
		}
	}
}
/****************************************************************************************************/
/*　LCDフリップ		：void	lcdFlip(void)															*/
/*																									*/
/* 機能　：LCDキャラクタバッファ（lcd_chr[4][16]）の内容をフォント展開し，LCDに表示する					*/
/*																									*/
/* 引数　：なし																						*/
/*																									*/
/* 戻り値：なし																						*/
/****************************************************************************************************/
void	LCD::lcdFlip(void){								/* LCDキャラクタバッファをイメージ展開し表示	*/
	int		ud, line, culm, i, j, k;
	char	*s_ptr = &lcdChar[0][0];					/* LCDキャラクタバッファアドレス（lcd_chr）	*/
	PGM_P	f_ptr;										/* font データアドレス						*/
	char	*i_ptr;										/* イメージバッファアドレス（lcd_img）			*/

	/* LCD表示キャラクタ情報をフォントデータとして展開する												*/
	while( s_ptr <= &lcdChar[3][15]){					/* LCDキャラクタバッファの最後までフォント展開	*/
		for( line=0; line<4; line++){					/* 4行分のデータを展開する					*/
			for( culm=0; culm<16; culm++){				/* 各行16文字分のデータを展開する				*/
				f_ptr = &fnt[(*s_ptr-0x20)*0x10];		/* フォントの先頭アドレス取得					*/
				for( ud=0; ud<2; ud++){					/* 上下順にイメージバッファへ展開				*/
					for( i=0; i<8; i++){				/* フォント8Byte を転送						*/
						lcdImage[line][ud][culm][i] = pgm_read_byte(f_ptr);
						f_ptr++;						/* フォントデータアドレス更新					*/
					}
				}
				s_ptr++;								/* LCDキャラクタバッファアドレス更新			*/
			}
		}
	}

	/* フォントデータをSSD1615にI2Cで転送する															*/
	i_ptr = &lcdImage[0][0][0][0];						/* イメージバッファの先頭アドレスをセット		*/
	/* 8行（2行で1文字分の表示となる）分のフォントデータを転送											*/
	for( i=0; i<8; i++){
		twiStart();										/* I2C 通信開始								*/
		twiSend(0b10000000);							/* アドレスデータ送信							*/
		twiSend(0xB0 | i);								/* ページアドレス送信							*/
		twiStop();										/* 送信終了									*/
		/* 1行（2行で1文字分の表示となる）分のフォントデータを転送										*/
		for( j=0; j<16; j++){							/* 16×8カラムの表示データ送信					*/
			twiStart();									/* I2C 通信開始								*/
			twiSend(0b01000000);						/* 表示データ送信								*/
			/* 1キャラクタ分のフォントを転送															*/
			for( k=0; k<8; k++){						/* 8カラム分の表示データ送信					*/
				twiSend(*i_ptr);						/* 表示データ1カラム転送						*/
				i_ptr++;
			}
			twiStop();									/* 8カラム分の表示データ送信完了				*/
		}
	}
}

/****************************************************************************************************/
/*　メモリFill		：void	memfill( char *ptr, char data, int length)								*/
/*																									*/
/* 機能　：メモリを任意の値で埋める．																	*/
/*																									*/
/* 引数　：char	*ptr			：　Fillするメモリの先頭アドレス										*/
/*		  char	data			：　メモリを埋める値													*/
/*		  int	length			：　メモリを埋めるバイト数												*/
/*																									*/
/* 戻り値：なし																						*/
/****************************************************************************************************/
void	LCD::memFill( char *ptr, char data, int length){
	int		i;
	for( i=0; i<length; i++){							/* バイト長の回数繰り返す						*/
		*ptr = data;									/* 指定データを1バイト書き込む					*/
		ptr++;											/* 書き込み先アドレスを1進める					*/
	}
}
