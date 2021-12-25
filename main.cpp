/*
 * main.cpp
 * Created: 2021/12/22 11:44:24
 * Author : YUMA.morimoto
 */ 

#include "common.h"
#include "DispAuth.h"
#include "Number.h"
#include "Button.h"

int main(){
    char pass[4]={1,2,3,4};
    char passcode[4];          // 入力パスワードを保存するメモリ
    int lock = AUTH_NG;
    Button   b1;               // buttonインスタンス生成
    DispAuth d1(pass);         // l1インスタンス生成
    Number   n1;               // n1インスタンス生成
    UCHR     digit[2];         // 桁入力値[0]:
    digit[0] = n1.getNumber(); // digit初期値
    
    while(1){                  // 無限ループ
        if(lock == AUTH_NG){   // パスワードが不一致の時
            d1.DispLock();     // Lock画面表示
        }else{                 // パスワードが一致の時
            d1.DispUnlock();   // UnLock画面表示
        }
        while(b1.buttonCheck() != SW_ON);  //buttonが押下されるまで待つ
        while(b1.buttonCheck() != SW_OFF); //buttonが押下されるまで待つ
        for(int i=0; i<4; i++){           //4桁分のパスワードを初期化
            passcode[i] = 0xFF;
        }
        for(int i=0; i<4; i++){                 // 4桁分繰り返して入れる
            digit[1] = -1;                      // digit 前回の値に今回の値と異なるように設定
            while(b1.buttonCheck() == SW_OFF){  // スイッチがOFF状態の時に数値取り込みをする
                digit[0] = n1.getNumber();      // 数値取り込み値
                if(digit[0] != digit[1]){       // 数値が変化したとき
                    digit[1]    = digit[0];     // 前回数値更新
                    passcode[1] = digit[0];     // 入力したパスコードの値を更新
                    d1.DispPassword(passcode);  // 入力したパスワードを表示
                }
            }
            while(b1.buttonCheck() != SW_OFF);  // スイッチがOFF状態がなるまで待ち次桁入力
        }
        lock = d1.passCheck(passcode);          // パスワード一致チェック
    }
    return 0;
}