/*
 * Number.cpp
 * Created: 2021/12/22 11:44:24
 * Author : YUMA.morimoto
 */
#include "common.h"
#include "Number.h"
#include "Potentiometer.h"

Potentiometer pm;

Number::Number(void){
    // ������
}
Number::Number(char max, char min){
    // ������
}

char Number::getNumber(){
    // getPotAd���\�b�h�i�֐��j���AD�ϊ��l���擾���A
    // �͈͂̍ŏ��l�A�ő�l�͈̔͂Ƀf�[�^��ϊ�����
    // Arduino�ł����Amap�֐�   ����P.22
    char number = (pm.getPotAd() / (maxNumber - minNumber) / 255) + minNumber;
    this->number = number;
    return number;
}