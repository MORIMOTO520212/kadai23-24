/*
 * Potentiometer.cpp
 * Created: 2021/12/16 13:24:57
 * Author: YUMA.morimoto
 */

#include "common.h"
#include "Potentiometer.h"

/* コンストラクタ */
Potentiometer::Potentiometer(void){
    DDRC  &= 0b11111110;    // PCD端子を入力ポートに設定
    ADCSRA = 0b10000100;    // A/D許可、A/D変換c1=ck/16
    ADMUX  = 0b01100000;    // AVCC基準、左揃え、ADC0を変換
    this->potAd = 0;        // 2直化闘値defalt
    this->threshold = 0x80; // 2値化闘値
}


Potentiometer::Potentiometer(UCHR threshold){
	DDRC  &= 0b11111110;       // PCD端子を入力ポートに設定
	ADCSRA = 0b10000100;       // A/D許可、A/D変換c1=ck/16
	ADMUX  = 0b01100000;       // AVCC基準、取得データ左揃え、ADC0を変換
	this->potAd=0;             // A/D変換結果初期値設定
	this->threshold=threshold; // 2値化闘値に引数の値を代入
}

/* 既存の閾値でHighLowを決める */
UCHR Potentiometer::getHL(void){
    UCHR POT_HIGH = 1;
    UCHR POT_LOW  = 0;
	UCHR ret = POT_HIGH;               // 戻り値Highを初期値設定
	if(getPotAd() < this->threshold){  // A/D値が闘値未満の時
		ret = POT_LOW;                 // 戻り値Lowを設定
	}
	return ret;
}

/* 引数で指定した閾値でHighLowを決める */
UCHR Potentiometer::getHL(UCHR threshold){
    UCHR POT_HIGH = 1;
    UCHR POT_LOW  = 0;
	UCHR ret = POT_HIGH;               // 戻り値Highを初期値設定
	if(getPotAd() < this->threshold){  // A/D値が闘値未満の時
		ret = POT_LOW;                 // 戻り値Lowを設定
	}
	return ret;
}

/* 8bitA/D変換結果読出 */
UCHR Potentiometer::getPotAd(void){
    ADCSRA |= 0b01000000;
    while((ADCSRA & 0b01000000) != 0);
    this->potAd = ADCH;
    this->threshold = threshold;
    return this->potAd;
}