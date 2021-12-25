/*
 * Potentiometer.cpp
 * Created: 2021/12/16 13:24:57
 * Author: YUMA.morimoto
 */

#include "common.h"
#include "Potentiometer.h"

/* �R���X�g���N�^ */
Potentiometer::Potentiometer(void){
    DDRC  &= 0b11111110;    // PCD�[�q����̓|�[�g�ɐݒ�
    ADCSRA = 0b10000100;    // A/D���AA/D�ϊ�c1=ck/16
    ADMUX  = 0b01100000;    // AVCC��A�������AADC0��ϊ�
    this->potAd = 0;        // 2�������ldefalt
    this->threshold = 0x80; // 2�l�����l
}


Potentiometer::Potentiometer(UCHR threshold){
	DDRC  &= 0b11111110;       // PCD�[�q����̓|�[�g�ɐݒ�
	ADCSRA = 0b10000100;       // A/D���AA/D�ϊ�c1=ck/16
	ADMUX  = 0b01100000;       // AVCC��A�擾�f�[�^�������AADC0��ϊ�
	this->potAd=0;             // A/D�ϊ����ʏ����l�ݒ�
	this->threshold=threshold; // 2�l�����l�Ɉ����̒l����
}

/* ������臒l��HighLow�����߂� */
UCHR Potentiometer::getHL(void){
    UCHR POT_HIGH = 1;
    UCHR POT_LOW  = 0;
	UCHR ret = POT_HIGH;               // �߂�lHigh�������l�ݒ�
	if(getPotAd() < this->threshold){  // A/D�l�����l�����̎�
		ret = POT_LOW;                 // �߂�lLow��ݒ�
	}
	return ret;
}

/* �����Ŏw�肵��臒l��HighLow�����߂� */
UCHR Potentiometer::getHL(UCHR threshold){
    UCHR POT_HIGH = 1;
    UCHR POT_LOW  = 0;
	UCHR ret = POT_HIGH;               // �߂�lHigh�������l�ݒ�
	if(getPotAd() < this->threshold){  // A/D�l�����l�����̎�
		ret = POT_LOW;                 // �߂�lLow��ݒ�
	}
	return ret;
}

/* 8bitA/D�ϊ����ʓǏo */
UCHR Potentiometer::getPotAd(void){
    ADCSRA |= 0b01000000;
    while((ADCSRA & 0b01000000) != 0);
    this->potAd = ADCH;
    this->threshold = threshold;
    return this->potAd;
}