/*
 * Potentiometer.h
 * Created: 2021/12/16 13:27:44
 *  Author: YUMA.morimoto
 */

#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

class Potentiometer{
	UCHR potAd;                    /* potentiometerA/D�l */
	UCHR threshold;                /* 2�������l */
	public:
	Potentiometer(void);           /* �R���X�g���N�^ */
	Potentiometer(UCHR threshold); /* �R���X�g���N�^���l */
	UCHR getPotAd(void);           /* 8bitA/D�ϊ����ʓǏo */
	UCHR getHL(void);              /* 2�����o�� */
	UCHR getHL(UCHR threshold);    /* 2�����o�͒l */
};

#endif /* POTENTIOMETER_H_ */