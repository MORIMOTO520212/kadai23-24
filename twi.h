/********************************************************************************/
/*	twi class																	*/
/*																				*/
/*　本ファイルは Grove Beginner Kit にてI2C通信を行うためのtwi class を定義した		*/
/*	ものである．																	*/
/*																				*/
/*	■制約事項																	*/
/*　		・Atmega328 CPUのSCL及びSDA端子にI2Cデバイスが接続されているものとする．		*/ 
/*		・ライセンスはGPLに準じるものとする．										*/
/*																				*/
/********************************************************************************/
/*	変更履歴																		*/
/*　識別子	日付			氏名					変更内容								*/
/*　#000		2021.07.26	荒金 匡徳			初版リリース							*/
/********************************************************************************/
#ifndef TWI_H_
#define TWI_H_

#include 	"common.h"							/* 共通ヘッダファイル				*/

/* 状態値定義																	*/
#define	START		0x08						/* スタート状態値					*/
#define	MT_SLA_ACK	0x18						/* SLA_Wを正常送信チェック値		*/
#define	MT_DATA_ACK	0x28						/* データを正常送信チェック値		*/

class twi{
	UCHR	slaveAddress;						/* スレーブデバイスアドレス		*/
public:
	twi( UCHR slave_address);					/* コンストラクタ					*/
	void	twiStart( void);					/* TWI 通信開始					*/
	void	twiSend(UCHR twi_data);				/* TWI データ送信				*/
	void	twiStop(void);						/* TWI データ送信終了				*/
	UCHR	twiRcv(UCHR *data, UCHR length);	/* TWI データ受信				*/
	void	twiError(int cd);					/* エラー発生時用メソッド			*/
};
#endif /* TWI_H_ */