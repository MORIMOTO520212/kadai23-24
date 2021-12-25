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
    // 初期化
}
Number::Number(char max, char min){
    // 初期化
}

char Number::getNumber(){
    // getPotAdメソッド（関数）よりAD変換値を取得し、
    // 範囲の最小値、最大値の範囲にデータを変換する
    // Arduinoでいう、map関数   資料P.22
    char number = (pm.getPotAd() / (maxNumber - minNumber) / 255) + minNumber;
    this->number = number;
    return number;
}