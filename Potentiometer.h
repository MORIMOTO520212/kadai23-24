/*
 * Potentiometer.h
 * Created: 2021/12/16 13:27:44
 *  Author: YUMA.morimoto
 */

#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

class Potentiometer{
	UCHR potAd;                    /* potentiometerA/D値 */
	UCHR threshold;                /* 2直化闘値 */
	public:
	Potentiometer(void);           /* コンストラクタ */
	Potentiometer(UCHR threshold); /* コンストラクタ闘値 */
	UCHR getPotAd(void);           /* 8bitA/D変換結果読出 */
	UCHR getHL(void);              /* 2直化出力 */
	UCHR getHL(UCHR threshold);    /* 2直化出力値 */
};

#endif /* POTENTIOMETER_H_ */