#include "Button.h"

/* Button状態取得関数 */
char Button::buttonCheck(void){
    char ret = SW_UNKNOWN; // 戻り値に初期化を入れる
    char btn_old;          // Button状態保持変数
    btn_old = PIND;        // PORTDのbit以外をマスク保持
    _delay_ms(10);         // 10ms間待つ
    if(((btn_old^PIND) & 0b01000000)==0){  // Buttonの変化がない時
        ret = (btn_old & 0b01000000) >> 6; // Buttonのbitを移動して初期化する
    }
    return ret;
}